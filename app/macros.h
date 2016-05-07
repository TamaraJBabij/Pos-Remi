#pragma once

#include "TTree.h"
#include "TH1D.h"
#include "DataSet.h"
#include "HistogramPair.h"
#include "HistogramTimeSums.h"
#include "FitSet.h"
#include "Event.h"
#include "PitchPropSet.h"


TTree* readWriteTree(TTree* tree);
DataSet* loadFromTree(TTree* tree);
TH1D* plotTimeSpectra(TTree* tree);
HistogramPair plotTimeSpectraDS(DataSet* data);
void constructEvents(DataSet* data);
HistogramTimeSums calculateTimeSums(DataSet* data);
void plotTimeSums(HistogramTimeSums timesums);
void checkTimeSums(DataSet* data, FitSet fits);
void identifyAndTime(DataSet* data);
void selectPosIonElec(DataSet* data);
void checkReconstructable(DataSet* data);
PitchPropSet calculatePitchProp(FitSet fits);
DataSet sortReconData(DataSet* data);
void convertLayerPosition(DataSet* reconData, PitchPropSet Pitches);
void convertCartesianPosition(DataSet* reconData);

