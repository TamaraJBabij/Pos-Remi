// creats histogram of time of flights (given by MCP signal) of the particles. 
#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "HistogramPair.h"

// returns histogram
// return type, function name(argument)
// where DataSet is returned from the tree reader



HistogramPair plotTimeSpectra(DataSet* dataset) {
	HistogramPair hist;
	TH1D* histpositive = new TH1D("hpos", "TimeSpectra positive", 200, -100, 32000);
	//histnegative = new TH1D ("hneg","TimeSpectra negative",200,-100,32000);
	for (Group* group : dataset) {
		for (Hit h : group) {
			if (h.channel == ChannelID::mcp) {
				if (h.detector == DetectorID::pos) {
					histpositive->Fill(h.time);
				}
				//else if(hit.detector == DetectorID::neg){
				//histnegative->Fill(h.time);
				//}
			}
		}
		histpositive->Draw();
	}
}
//Draw histograms, which represent time spectra relative to the positron hit
//Want to export histogram data as well as save time spectra figures
//need to set up canvas first

//hist.negative->Draw();