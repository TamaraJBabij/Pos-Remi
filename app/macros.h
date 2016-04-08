#pragma once

#include "TTree.h"
#include "TH1D.h"
#include "DataSet.h"
#include "HistogramPair.h"
#include "HistogramTimeSums.h"


TTree* readWriteTree(TTree* tree);
DataSet* loadFromTree(TTree* tree);
TH1D* plotTimeSpectra(TTree* tree);
HistogramPair plotTimeSpectraDS(DataSet* data);
void constructEvents(DataSet* data);
HistogramTimeSums calculateTimeSums(DataSet* data);
void checkTimeSums(DataSet* data);
void plotTimeSums(HistogramTimeSums timesums);