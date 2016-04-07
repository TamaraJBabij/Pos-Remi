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

using namespace std;

int main(int argc, char* argv[]) {
	//Initial function to set up the debug environment
	int setUpDebugEnvironment();
	//initialises root app
	TApplication* rootapp = new TApplication("example", &argc, argv);
	TFile* rawFile = TFile::Open("../parsed.root");
	TTree* rawTree = (TTree*)rawFile->Get("T");
	//TTree* tree = readWriteTree(rawTree);


	DataSet* data = loadFromTree(rawTree);

	rawFile->Close();

	//tree->Draw("Time");
	HistogramPair hists = plotTimeSpectraDS(data);

	// need to switch between canvases in root in order to creat two histograms
	//any instance of TCanvas can be subdivided into independent graphical areas, 
	//called pads (by default, a canvas contain a single pad, occupying the whole space - TCanvas inherits from TPad).


	TCanvas c1("c1", "First Canvas");
	//TPad::Divide() specifies number of vertical and horizontal slices of canvas
	c1.Divide(1,2);
	c1.cd(1);
	hists.positive->Draw();
	//hists.positive->Write();
	//Just defual draw hist option offers irrelavnt info for time spectrum
	//gStyle->SetOptStat("");
	c1.cd(2);
	//TFile f("histos.root", "new");
	hists.negative->Draw();
	//hists.negative->Write();

	//Associate hits into events, where event is a single particle/ion hit on the detector. Events are sorted by group
	constructEvents(data);

	// construct timesum histograms
	HistogramTimeSums timesums = calculateTimeSums(data);

	//Store fit parameters into a tree for later accessing
	// setting up tree
	TFile file("TimeSumTree.root", "recreate");
	TTree treeTS("TimeSumPeaks", "simple tree that stores timesum peaks and sigma");
	//Cant store strings in tree?
	Double_t peak, sigma, error;
	//Char_t layer;
	//treeTS.Branch("Layer", &layer);
	treeTS.Branch("Peak", &peak);
	treeTS.Branch("Sigma", &sigma);
	treeTS.Branch("Error", &error);
	
	TCanvas c2("c2", "Second Canvas");
	//set up canvas for time sums - 3 for each detector - 6 in total
	//TPad::Divide() specifies number of vertical and horizontal slices of canvas
	c2.Divide(2, 3);
	c2.cd(1);
	timesums.layer_upos->Draw();
	timesums.layer_upos->Fit("gaus");
	gStyle->SetOptFit(0011);
	//timesums.layer_upos->Write();
	//timesums.layer_upos->Write();
	//need ot make fit persistent for this method to work
	TF1 *fit = timesums.layer_upos->GetFunction("gaus");
	//layer = layer_upos;
	peak = fit->GetParameter(1);
	//std::cout << fit->GetParameter(1) << endl;
	sigma = fit->GetParameter(2);
	error = fit->GetParError(1);
	treeTS.Fill();
	//Want to display fit parameters on timesums plots
	//timesums.layer_upos->SetOptFit();

	c2.cd(2);
	timesums.layer_vpos->Draw();
	timesums.layer_vpos->Fit("gaus");
	c2.cd(3);
	timesums.layer_wpos->Draw();
	timesums.layer_wpos->Fit("gaus");
	c2.cd(4);
	timesums.layer_uneg->Draw();
	timesums.layer_uneg->Fit("gaus");
	c2.cd(5);
	timesums.layer_vneg->Draw();
	timesums.layer_vneg->Fit("gaus");
	c2.cd(6);
	timesums.layer_wneg->Draw();
	timesums.layer_wneg->Fit("gaus");

	//Want to write timesum information to tree for accessing later in program, also to save to csv such that
	//ts info for all runs can be accessed at later dates without rerunning code
	treeTS.Write();

	rootapp->Run();



    return 0;
}

