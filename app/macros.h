#pragma once

#include "TTree.h"
#include "TH1D.h"
#include "DataSet.h"
#include "HistogramPair.h"

TTree* readWriteTree(TTree* tree);
DataSet* loadFromTree(TTree* tree);
TH1D* plotTimeSpectra(TTree* tree);
HistogramPair plotTimeSpectraDS(DataSet* data);