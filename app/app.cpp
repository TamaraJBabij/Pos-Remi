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
#include "DataSet.h"
#include "TFile.h"
#include "HistogramPair.h"
#include "TObject.h"
#include "Event.h"
#include "HistogramTimeSums.h"

using namespace std;

int main(int argc, char* argv[]) {
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
	c1.cd(2);
	hists.negative->Draw();

	//Associate hits into events, where event is a single particle/ion hit on the detector. Events are sorted by group
	constructEvents(data);

	// construct timesum histograms
	HistogramTimeSums timesums = calculateTimeSums(data);

	//Store fit parameters into a tree for later accessing
	// setting up tree
	TTree treeTS("TimeSumPeaks", "simple tree that stores timesum peaks and sigma");
	//Cant store strings in tree?
	Double_t peak, sigma;
	treeTS.Branch("Peak", &peak);
	treeTS.Branch("Sigma", &sigma);
	
	TCanvas c2("c2", "Second Canvas");
	//set up canvas for time sums - 3 for each detector - 6 in total
	//TPad::Divide() specifies number of vertical and horizontal slices of canvas
	c2.Divide(2, 3);
	c2.cd(1);
	timesums.layer_upos->Draw();
	timesums.layer_upos->Fit("gaus");

	//Want to display fit parameters on timesums plots
	//timesums.layer_upos->SetOptFit();
	c2.cd(2);
	timesums.layer_vpos->Draw();
	timesums.layer_vpos->Fit("gaus");
	TF1 *fit = timesums.layer_vpos->GetFunction("gaus");
	peak = fit->GetParameter(1);
	sigma = fit->GetParameter(2);
	treeTS.Fill();
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

	rootapp->Run();



    return 0;
}

