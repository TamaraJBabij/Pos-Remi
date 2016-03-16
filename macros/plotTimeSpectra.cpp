// creats histogram of time of flights (given by MCP signal) of the particles. 
#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "HistogramPair.h"
#include <vector>

// returns histogram
// return type, function name(argument)
// where DataSet is returned from the tree reader



HistogramPair plotTimeSpectra(TTree* tree) {
	Int_t GroupNumber, Channel;
	Double_t Time;
	tree->SetBranchAddress("GroupNumber", &groupNumber);
	tree->SetBranchAddress("Channel", &channel);
	tree->SetBranchAddress("Time", &time);

	HistogramPair hist;
	hist.positive = new TH1D("hpos", "TimeSpectra positive", 200, -100, 32000);
	hist.negative = new TH1D("hneg", "TimeSpectra negative", 200, -100, 32000);

	int N = (int)tree->GetEntries();
	for (int i = 0; i < N; i++) {
		tree->GetEntry(i);

		switch (Channel) {
		case CFG_CHANNEL_POS_CP2:
			hist.positive->Fill(h.time);
			break
		case CFG_CHANNEL_ELEC_CP2:
			hist.negative->Fill(h.time);
			break
			}
		}
		hist.positive->Draw();
	}
	return hist;
}
//Draw histograms, which represent time spectra relative to the positron hit
//Want to export histogram data as well as save time spectra figures
//need to set up canvas first

//hist.negative->Draw();