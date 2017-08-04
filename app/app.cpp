// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "macros.h"
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TFormula.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include "DataSet.h"
#include "TFile.h"
#include "HistogramPair.h"
#include "TObject.h"
#include "Event.h"
#include "HistogramTimeSums.h"
#include "HistogramXY.h"
#include "configlayers.h"
#include "Constants.h"
#include "FitSet.h"
#include <TStyle.h>
#include "histogramElecLayers.h"
#include "histogramElecLayers.h"
#include <TGraph.h>
#include <TLegend.h>
#include "dirent.h"

using namespace std;

/* Pos-Remi Full analysis 
* Code takes in raw DAQ tree files from the 2016 DAQ code authored by Dan Murtagh. The trees are read in and converted to c++ 
* objects, these are then processed and sorted into reconstructable triple events. Criteria for a reconstructable triple event
* is a positron hit, Ar+ hit and an electron hit, with the electron and positron hits having at least 2 layer hits (u1, u2 and w1, w2 for example)
* such that an X,Y reconstruction can be made. 
* Author: Tamara J Babij
* Version control of software found on: https://github.com/TamaraJBabij/Pos-Remi
*/

int main(int argc, char* argv[]) {
	//Initial function to set up the debug environment
	int setUpDebugEnvironment();
	//initialises root app
	TApplication* rootapp = new TApplication("C:/Users/Tamara/Documents/GitHub/Pos-Remi/", &argc, argv);

	//Two possible options, this allows for sorting through raw DAQ trees for valid events only once
	// while still allowing for many iterations of X,Y imaging of valid triple events
	string loadtype;
	cout << "Would you like to run program to read in DAQ files and write to a reconTree (type: write), or to load a reconTree (type: load)" << endl;
	cin >> loadtype;
	posremiLoadType sessionOption;
	if (loadtype.compare("write") == 0) {
		sessionOption = reconTreeWrite;
	}
	else if (loadtype.compare("load") == 0) {
		sessionOption = reconTreeLoad;
	}

	//scans folder created by the DAQ software and loads all tree ( .root) files into the dataset
	//not currently neccasary for the load options
	string fileLocation;
	cout << "what is the directory? remember to add a backslash at the end" << endl;
	cin >> fileLocation;

	//Set up canvas
	gStyle->SetPalette(1);
	double_t width = 800;
	double_t height = 800;

	int reconTriplesCount = 0;

	// need to switch between canvases in root in order to creat two histograms
	//any instance of TCanvas can be subdivided into independent graphical areas, 
	//called pads (by default, a canvas contain a single pad, occupying the whole space - TCanvas inherits from TPad).
	TCanvas c1("c1", "First Canvas");
	//st up hist pair from which graphs will be drawn
	//Histogram which will contain absolute time spectra of all MCP hits
	HistogramPair hists;
	hists.positive = new TH1D("hpos", "TimeSpectrum positive", 500, 0, 32000);
	hists.negative = new TH1D("hneg", "TimeSpectrum negative", 500, 0, 32000);
	//TPad::Divide() specifies number of vertical and horizontal slices of canvas
	c1.Divide(1, 2);
	c1.cd(1);
	hists.positive->Draw();
	//Just defualt draw hist option offers irrelavnt info for time spectrum
	c1.cd(2);
	hists.negative->Draw();

	//Histogram that will store absolute TOF info for the reconstructable triple events only
	HistogramPair TripleTOFHist;
	TripleTOFHist.positive = new TH1D("hpos", "TOF Triples positive", 500, 0, 32000);
	TripleTOFHist.negative = new TH1D("hneg", "TOF Triples negative", 500, 0, 32000);
	TCanvas TOFTriples("TOF Triples", "TOF Triples");
	TOFTriples.Divide(1, 2);
	TOFTriples.cd(1);
	TripleTOFHist.positive->Draw();
	TOFTriples.cd(2);
	TripleTOFHist.negative->Draw();

	//Store fit parameters into a tree for later accessing
	//setting up tree
	TFile file("TimeSumTree.root", "recreate");
	TTree treeTS("TimeSumPeaks", "simple tree that stores timesum peaks and sigma");
	//Cant store strings in tree?
	Double_t peak, sigma, error;
	//Will define layer numbers in configuration.h file
	//not sure if text/string can be stored in trees
	Double_t layer;
	treeTS.Branch("Layer", &layer);
	treeTS.Branch("Peak", &peak);
	treeTS.Branch("Sigma", &sigma);
	treeTS.Branch("Error", &error);

	HistogramTimeSums timesums;
	timesums.layer_upos = new TH1D("upos", "TimeSum upos layer", 800, 100, 200);
	timesums.layer_vpos = new TH1D("vpos", "TimeSum vpos layer", 800, 100, 180);
	timesums.layer_wpos = new TH1D("wpos", "TimeSum wpos layer", 800, 100, 180);
	timesums.layer_uneg = new TH1D("uneg", "TimeSum uneg layer", 800, 0, 200);
	timesums.layer_vneg = new TH1D("vneg", "TimeSum vneg layer", 800, 0, 200);
	timesums.layer_wneg = new TH1D("wneg", "TimeSum wneg layer", 800, 0, 200);

	TCanvas c2("c2", "Second Canvas");

	HistogramXY XYpositions;
	XYpositions.positronDET = new TH2D("positronDET", "Positrons", 200, -60, 60,200, -60, 60);
	XYpositions.electronDET = new TH2D("electronDET", "Electrons", 200, -60, 60, 200, -60, 60);
	XYpositions.ionDET = new TH2D("ionDET", "Ions", 200, -60, 60, 200, -60, 60);
	/*
	Histograms electron layers
	HistogramElecLayers UVWlayers;
	UVWlayers.UVlayers = new TH2D("electronDet", "UV layer", 2000, -60, 60, 2000, -60, 60);
	UVWlayers.UWlayers = new TH2D("electronDET", "UW layer", 2000, -60, 60, 2000, -60, 60);
	UVWlayers.VWlayers = new TH2D("electronDET", "VW layer", 2000, -60, 60, 2000, -60, 60);
	*/

	TCanvas c3("c3", "Third Canvas", width, height);
	//works better with more runs and a contour plot, 
	//since plotting individual runs intensity is 1, need to implement contours
	//XYpositions.positronDET->Draw("colz");
	XYpositions.positronDET->Draw("colz");

	TCanvas c4("c4", "Fourth Canvas", width, height);
	XYpositions.electronDET->Draw("colz");

	TCanvas c5("c5", "Fifth Canvas", width, height);
	XYpositions.ionDET->Draw("colz");

	FitSet fits;

	//Need to iterate through each tree, only do timesums 

	int filenumber = 0;
	DIR* dir;
	dirent* pdir;
	dir = opendir(fileLocation.c_str());
	bool firstFile = true;
	vector<char*> files;

	//Prints out triple coincidence info to .csv
	ofstream tripleData;
	int tripleCount = 0;
	tripleData.open(fileLocation + "tripleData.csv");
	tripleData << "Number of electrons identified, Event number, X pos (m), Y pos (m), X elec (m), Y elec (m), Rpos (m), Relec (m)" << endl;

	//Due to the large number of background now that certain logic has been removed from the DAQ hardware, 
	// want to be able to investigate the particle identifcation and how much background each event has
	// printing this to .csv allows for investigation easily
	ofstream tripleIdInfo;
	int tripleIdcount = 0;
	tripleIdInfo.open(fileLocation + "tripleIdInfo.csv");
	tripleIdInfo << "Group ID, Particle ID, TOF, u pairs, v pairs, w pairs, recon event" << endl;

	//Want to monitor triples rate per tree, this csv will print out the triple count for each tree
	ofstream tripleTreeRate;
	tripleTreeRate.open(fileLocation + "tripleTreeRate.csv");
	tripleTreeRate << "Triples per tree" << endl;


	//calculate pitch propogation
	PitchPropSet Pitches = calculatePitchProp();
	
	//Sets up loop through all files
	if (sessionOption == reconTreeWrite) {
		//option for rading through raw DAQ files and saving valid triple events to reconTree
		//Prepare reconTree
		//reconTree will save info for all valid triple hits, such that they can be reanalysed faster
		//Declare trees to write to

		TFile reconTriplesFile("reconTriplesTree2.root", "recreate");
		TTree reconTriplesTree("Reconstructable Triples Tree", "Tree that stores valid triple hits");
		bool ULayer = false;
		bool VLayer = false;
		bool WLayer = false;
		//AbsTOF is the absolute time of flight of the particles
		Double_t u1Time, u2Time, v1Time, v2Time, w1Time, w2Time, TimeFromPos, AbsTOF;
		Int_t GroupNumber = 0;
		Int_t DetectorType, ParticleType;
		//set up tree branches
		reconTriplesTree.Branch("GroupNumber", &GroupNumber);
		reconTriplesTree.Branch("Detector", &DetectorType);
		reconTriplesTree.Branch("Particle", &ParticleType);
		reconTriplesTree.Branch("TimeRel", &TimeFromPos);
		reconTriplesTree.Branch("TimeAbs", &AbsTOF);
		reconTriplesTree.Branch("ULayer", &ULayer);
		reconTriplesTree.Branch("u1Time", &u1Time);
		reconTriplesTree.Branch("u2Time", &u2Time);
		reconTriplesTree.Branch("VLayer", &VLayer);
		reconTriplesTree.Branch("v1Time", &v1Time);
		reconTriplesTree.Branch("v2Time", &v2Time); 
		reconTriplesTree.Branch("WLayer", &WLayer);
		reconTriplesTree.Branch("w1Time", &w1Time);
		reconTriplesTree.Branch("w2Time", &w2Time);

		if (dir != NULL) {
			while (pdir = readdir(dir)) {
				char* fileName = pdir->d_name;
				if (strlen(fileName) > 5 && !strcmp(fileName + strlen(fileName) - 5, ".root")) {
					//Intialise storage container for data from tree
					DataSet* data = new DataSet();
					//using string Folder Name acquire intiial tree
					//Initial tree is given by ReMinumber with no underscore number
					//cout << fileName << endl;
					char str[256];
					strcpy(str, fileLocation.c_str());
					strcat(str, fileName);
					//cout << str << endl;
					cout << filenumber << endl;
					filenumber++;

					TFile* rawFile = TFile::Open(str);
					TTree* rawTree = (TTree*)rawFile->Get("T");
					loadFromTreeDataSet(rawTree, data);
					rawFile->Close();



					//Associate hits into events, where event is a single particle/ion hit on the detector. Events are sorted by group
					constructEvents(data);

					if (firstFile) {
						firstFile = false;
						//construct timesum histograms
						calculateTimeSums(data, timesums);

						//Want to write timesum information to tree for accessing later in program, also to save to csv such that
						//ts info for all runs can be accessed at later dates without rerunning code
						treeTS.Write();

						//set up canvas for time sums - 3 for each detector - 6 in total
						//TPad::Divide() specifies number of vertical and horizontal slices of canvas
						c2.Divide(2, 3);

						c2.cd(1);
						timesums.layer_upos->Draw();
						timesums.layer_upos->Fit("gaus");
						gStyle->SetOptFit(0011);
						TF1 *fitu = timesums.layer_upos->GetFunction("gaus");
						layer = CFG_LAYER_UPOS;
						peak = fitu->GetParameter(1);
						sigma = fitu->GetParameter(2);
						error = fitu->GetParError(1);
						treeTS.Fill();
						fits.setFit(u, positive, peak, error, sigma);
						//Want to display fit parameters on timesums plots
						//timesums.layer_upos->SetOptFit();

						c2.cd(2);
						timesums.layer_vpos->Draw();
						timesums.layer_vpos->Fit("gaus");
						TF1 *fitv = timesums.layer_vpos->GetFunction("gaus");
						layer = CFG_LAYER_VPOS;
						peak = fitv->GetParameter(1);
						sigma = fitv->GetParameter(2);
						error = fitv->GetParError(1);
						treeTS.Fill();
						fits.setFit(v, positive, peak, error, sigma);

						c2.cd(3);
						timesums.layer_wpos->Draw();
						timesums.layer_wpos->Fit("gaus");
						TF1 *fitw = timesums.layer_wpos->GetFunction("gaus");
						layer = CFG_LAYER_WPOS;
						peak = fitw->GetParameter(1);
						sigma = fitw->GetParameter(2);
						error = fitw->GetParError(1);
						treeTS.Fill();
						fits.setFit(w, positive, peak, error, sigma);

						c2.cd(4);
						timesums.layer_uneg->Draw();
						timesums.layer_uneg->Fit("gaus");
						TF1 *fitun = timesums.layer_uneg->GetFunction("gaus");
						layer = CFG_LAYER_UNEG;
						peak = fitun->GetParameter(1);
						sigma = fitun->GetParameter(2);
						error = fitun->GetParError(1);
						treeTS.Fill();
						fits.setFit(u, negative, peak, error, sigma);

						c2.cd(5);
						timesums.layer_vneg->Draw();
						timesums.layer_vneg->Fit("gaus");
						TF1 *fitvn = timesums.layer_vneg->GetFunction("gaus");
						layer = CFG_LAYER_VNEG;
						peak = fitvn->GetParameter(1);
						sigma = fitvn->GetParameter(2);
						error = fitvn->GetParError(1);
						treeTS.Fill();
						fits.setFit(v, negative, peak, error, sigma);

						c2.cd(6);
						timesums.layer_wneg->Draw();
						timesums.layer_wneg->Fit("gaus");
						TF1 *fitwn = timesums.layer_wneg->GetFunction("gaus");
						layer = CFG_LAYER_WNEG;
						peak = fitwn->GetParameter(1);
						sigma = fitwn->GetParameter(2);
						error = fitwn->GetParError(1);
						treeTS.Fill();
						fits.setFit(w, negative, peak, error, sigma);

						c2.Modified();
						c2.Update();
					}

					/*
					FitData fit = fits.getFit(u, positive);
					cout << "U sigma: " << fit.sigma << endl;
					cout << "U peak: " << fit.peak << endl;
					*/

					//Checks timesums are within 2sigma of fitted peak
					checkTimeSums(data, fits);

					//plotTimeSpectraDS(data, hists);
					for (Group* g : *data) {
						for (Hit* h : *g) {
							if (h->channel == mcp) {
								if (h->detector == pos) {
									hists.positive->Fill(h->time);
								}
								else if (h->detector == neg) {
									hists.negative->Fill(h->time);
								}

							}
						}
					}

					//takes timedifferences of MCP hits for each event within a group
					//identifies particle and stores in MCPTDiff double
					//stored is the particleID and timedifference relative to positron
					identifyAndTime(data);

					// want to index number of particles and bool triple for each each group
					selectPosIonElec(data);

					//check each particle hit has enough information to reconstruct X Y position
					//not needed for ion
					checkReconstructable(data);

					//now need to check for all three particles (ion, pos, elec) and that the pos and elec have a reconBool
					//Copy over triple coincidences with reconstrutable particle hits to new dataset
					DataSet *reconData = sortReconData(data, reconTriplesCount);

					convertLayerPosition(reconData, Pitches);

					convertCartesianPosition(reconData, &XYpositions);

					//write triple info to a .csv, to be parsed into erics code
					for (Group* g : *reconData) {
						tripleData << "1," << tripleCount << ",";
						tripleData << g->positron.x / 1000 << "," << g->positron.y / 1000 << ",";
						tripleData << g->electron.x / 1000 << "," << g->electron.y / 1000 << ",";
						tripleData << g->positron.r / 1000 << "," << g->electron.r / 1000 << endl;
						tripleCount++;

					}

					for (Group* g : *data) {
						if (g->TripleCoinc == true) {
							for (Event *e : g->events) {
								tripleIdInfo << tripleIdcount << ",";
								tripleIdInfo << e->particletype << "," << e->timefrompos << ",";
								tripleIdInfo << e->uPairs.size() << "," << e->vPairs.size() << ",";
								tripleIdInfo << e->wPairs.size() << "," << g->recon << endl;
							}
							tripleIdcount++;
						}
					}

					for (Group* g : *reconData) {
						for (Event *e : g->events) {
							if (e->particletype == positron || e->particletype == ion1) {
								TripleTOFHist.positive->Fill(e->mcp->time);
							}
							else if (e->particletype == electron) {
								TripleTOFHist.negative->Fill(e->mcp->time);
							}
						}
					}

					//Want to save valid triples in to a reconTree such that data can quickly be reanlysed
					// as electron detectors are not calibrated this is neccasary
					
					
					for (Group* g : *reconData) {
						GroupNumber++;
						reconTriplesCount++;
						for (Event* e : g->events) {
							if (e->mcp->detector == pos) {
								DetectorType = 0;
							}
							else {
								DetectorType = 1;
							}
							if (e->uPairs.size() == 1) {
								ULayer = true;
								u1Time = e->uPairs.front().line1;
								u2Time = e->uPairs.front().line2;
								//cout << "u true" << endl;
							}
							else {
								ULayer = false;
								u1Time = 0;
								u2Time = 0;
							}
							if (e->vPairs.size() == 1) {
								VLayer = true;
								v1Time = e->vPairs.front().line1;
								v2Time = e->vPairs.front().line2;
							}
							else {
								VLayer = false;
								v1Time = 0;
								v2Time = 0;
							}
							if (e->wPairs.size() == 1) {
								WLayer = true;
								w1Time = e->wPairs.front().line1;
								w2Time = e->wPairs.front().line2;
								//cout << "w true" << endl;
							}
							else {
								WLayer = false;
								w1Time = 0;
								w2Time = 0;
							}
							ParticleType = e->particletype;
							cout << "Particle Type: " << ParticleType << endl;
							TimeFromPos = e->timefrompos;
							cout << "Time From Pos: " << TimeFromPos << endl;
							AbsTOF = e->reltimediff.timediff;
							cout << "Abs TOF: " << AbsTOF << endl;
							cout << "U layer: " << ULayer << "VLayer: " << VLayer << "W Layer: " << WLayer << endl;
							reconTriplesTree.Fill();
						}
					}
					

					tripleTreeRate << reconTriplesCount << endl;
					cout << "True Triples per tree rate: " << reconTriplesCount << endl;
					reconTriplesCount = 0;
					delete data;

					//histogram detector images with 2D histogram
					//histogramXYPositions(reconData, &XYpositions);
					//draw the detector images

					//histogramElectronLayers(reconData, UVWlayers);

					c2.Modified();
					c2.Update();
					c3.Modified();
					c3.Update();
					c4.Modified();
					c4.Update();
					c5.Modified();
					c5.Update();

				}
			}
			
		}
		reconTriplesFile.cd();
		reconTriplesTree.ResetBranchAddresses();
		reconTriplesTree.Write();
		reconTriplesTree.Print();
		reconTriplesFile.Close();
		
		
	}
	
	//loads valid triple events from the reconTree
	if (sessionOption == reconTreeLoad) {
		if (dir != NULL) {
			while (pdir = readdir(dir)) {
				char* fileName = pdir->d_name;
				if (strlen(fileName) > 5 && !strcmp(fileName + strlen(fileName) - 5, ".root")) {
					//Intialise storage container for data from tree
					DataSet* reconData = new DataSet();
					//using string Folder Name acquire intiial tree
					//Initial tree is given by ReMinumber with no underscore number
					//cout << fileName << endl;
					char str[256];
					strcpy(str, fileLocation.c_str());
					strcat(str, fileName);
					cout << filenumber << endl;
					cout << fileName << endl;
					filenumber++;
					//Loops through all .root files in the selected folder
					TFile* rawFile = TFile::Open(str);
					TTree* rawTree = (TTree*)rawFile->Get("Reconstructable Triples Tree");
					//loadFromTreeDataSet(rawTree, reconData);
					//takes the reconTree and loads it into a dataset that the code can process
					positionsTreeToDataSet(rawTree, reconData);
					
					//Closes raw file to save memory
					rawFile->Close();

					//Converts timing information relative to the MCP hit into a position hit along the delay line
					convertLayerPosition(reconData, Pitches);

					//Converts layer info into the X,Y co0ordinates
					convertCartesianPosition(reconData, &XYpositions);

					//Histogram the absolute MCP hits
					for (Group* g : *reconData) {
						for (Hit* h : *g) {
							if (h->channel == mcp) {
								if (h->detector == pos) {
									hists.positive->Fill(h->time);
								}
								else if (h->detector == neg) {
									hists.negative->Fill(h->time);
								}

							}
						}
					}

					//Histogram the relative timing to the positron (all "positron" hits will be at time 0)
					for (Group* g : *reconData) {
						for (Event *e : g->events) {
							if (e->particletype == positron || e->particletype == ion1) {
								TripleTOFHist.positive->Fill(e->mcp->time);
							}
							else if (e->particletype == electron) {
								TripleTOFHist.negative->Fill(e->mcp->time);
							}
						}
					}

					//closes loaded in data to save memory
					delete reconData;
					c1.Modified();
					c1.Update();
					TOFTriples.Modified();
					TOFTriples.Update();
					c2.Modified();
					c2.Update();
					c3.Modified();
					c3.Update();
					c4.Modified();
					c4.Update();
					c5.Modified();
					c5.Update();

	
				}
			}
		}
	}

	//updates modifed canvas
	c1.Modified();
	c1.Update();
	TOFTriples.Modified();
	TOFTriples.Update();
	rootapp->Draw();

	//closes csv file once all events have been written
	tripleData.close();
	tripleIdInfo.close();
	tripleTreeRate.close();
	closedir(dir);

	//allows for root graphs to be interactive, can zoom in etc
	rootapp->Run();

	return 0;
}

