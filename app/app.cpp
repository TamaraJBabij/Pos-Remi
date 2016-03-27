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

	hists.positive->Draw();	rootapp->Run();

    return 0;
}

