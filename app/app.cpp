// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
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
* Author: Tamara J Babij
* Version control of software found on: https://github.com/TamaraJBabij/CalibrateDetectors/
*/

int main(int argc, char* argv[]) {
	//Initial function to set up the debug environment
	int setUpDebugEnvironment();
	//initialises root app
	TApplication* rootapp = new TApplication("example", &argc, argv);

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
	HistogramPair hists;
	hists.positive = new TH1D("hpos", "TimeSpectrum positive", 500, 0, 32000);
	hists.negative = new TH1D("hneg", "TimeSpectrum negative", 500, 0, 32000);
	//TPad::Divide() specifies number of vertical and horizontal slices of canvas
	c1.Divide(1, 2);
	c1.cd(1);
	hists.positive->Draw();
	//Just defual draw hist option offers irrelavnt info for time spectrum
	c1.cd(2);
	hists.negative->Draw();
	
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
	timesums.layer_upos = new TH1D("upos", "TimeSum upos layer", 800, 120, 180);
	timesums.layer_vpos = new TH1D("vpos", "TimeSum vpos layer", 800, 100, 200);
	timesums.layer_wpos = new TH1D("wpos", "TimeSum wpos layer", 800, 120, 180);
	timesums.layer_uneg = new TH1D("uneg", "TimeSum uneg layer", 800, 40, 180);
	timesums.layer_vneg = new TH1D("vneg", "TimeSum vneg layer", 800, 40, 120);
	timesums.layer_wneg = new TH1D("wneg", "TimeSum wneg layer", 800, 0, 200);

	TCanvas c2("c2", "Second Canvas");

	HistogramXY XYpositions;
	XYpositions.positronDET = new TH2D("positronDET", "Positrons", 2000, -60, 60, 2000, -60, 60);
	XYpositions.electronDET = new TH2D("electronDET", "Electrons", 2000, -60, 60, 2000, -60, 60);
	XYpositions.ionDET = new TH2D("ionDET", "Ions", 2000, -60, 60, 2000, -60, 60);
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
	XYpositions.positronDET->Draw("cont0");

	TCanvas c4("c4", "Fourth Canvas", width, height);
	XYpositions.electronDET->Draw("cont0");

	TCanvas c5("c5", "Fifth Canvas", width, height);
	XYpositions.ionDET->Draw("cont0");

	FitSet fits;

	//scans folder created by the DAQ software and loads all tree ( .root) files into the dataset
	//not currently neccasary for the load options
	string fileLocation;
	cout << "what is the directory? remember to add a backslash at the end" << endl;
	cin >> fileLocation;

	//Need to iterate through each tree, only do timesums 

	int filenumber = 0;
	DIR* dir;
	dirent* pdir;
	dir = opendir(fileLocation.c_str());
	bool firstFile = true;
	vector<char*> files;
	//Sets up loop through all files
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

				//calculate pitch propogation
				PitchPropSet Pitches = calculatePitchProp();

				//Copy over triple coincidences with reconstrutable particle hits to new dataset


				DataSet *reconData = sortReconData(data, reconTriplesCount);

				convertLayerPosition(reconData, Pitches);

				convertCartesianPosition(reconData, &XYpositions);

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
	/** 
	 * Convert time to position info
	 *First off need to get U,V,W from u1 u2, v1 v2, w1 w2
	 *
	 */
	
	//TLegend* leg = new TLegend(0.1,0.7,0.3,0.9, "Layers");
	//leg->Draw();
	//leg->AddEntry(UVWlayers.UVlayers, "UV layer");
	//leg->AddEntry(UVWlayers.UWlayers, "UW layer");
	//leg->AddEntry(UVWlayers.VWlayers, "WV layer");
	//c6.Update();

	//differenceOfLayers(reconData);

	//HistogramDIFF UVWdifferences = histogramElecLayerDiff(reconData);
	//TCanvas c7("c7", "Layer Differences");
	//c7.Divide(2, 3);
	//c7.cd(1);
	//UVWdifferences.ydiffuv_uw->Draw();
	//c7.cd(2);
	//UVWdifferences.ydiffuv_vw->Draw();
	//c7.cd(3);
	//UVWdifferences.xdiffuv_vw->Draw();
	//c7.cd(4);
	//UVWdifferences.ydiffuw_vw->Draw();
	//c7.cd(5);
	//UVWdifferences.xdiffuw_vw->Draw();

	closedir(dir);

	c1.Modified();
	c1.Update();

	rootapp->Draw();

	rootapp->Run();

	//should print out metafile of setup, AND csv dump of data. 

	return 0;
}

