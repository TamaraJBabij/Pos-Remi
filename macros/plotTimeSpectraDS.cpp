#include "HistogramPair.h"
#include "TTree.h"
#include "TH1D.h"
#include "configuration.h"
#include "DataSet.h"

using namespace std;

 void plotTimeSpectraDS(DataSet* data, HistogramPair Hists) {

	//Histogram both positive and negative MCP detector pulses, all relative to positron time
	


	for (Group* g : *data) {
		for (Hit* h : *g) {
			if (h->channel == mcp) {
				if (h->detector == pos) {
					Hists.positive->Fill(h->time);
				}
				else if (h->detector == neg) {
					Hists.negative->Fill(h->time);
				}

			}
		}
	}
}