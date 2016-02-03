// creats histogram of time of flioghts (given by MCP signal) of the particles. 
#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "HistogramPair.h"

// returns histogram
// return type, function name(argument)
// where DataSet is returned from the tree reader



HistogramPair plotTimeSpectra(DataSet* dataset){
	HistogramPair h;
	h.positive = new TH1D("hpos","TimeSpectra positive",200,-100,32000)
	h.negative = new TH1D("hneg","TimeSpectra negative",200,-100,32000)
}