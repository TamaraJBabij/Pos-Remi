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
#include "DataSet.h"
#include "TFile.h"
#include "HistogramPair.h"
#include "TObject.h"

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
	hists.positive->Draw();	c1.cd(2);	hists.negative->Draw();	rootapp->Run();

    return 0;
}

