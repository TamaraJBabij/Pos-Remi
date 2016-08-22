#pragma once

#include "TTree.h"
#include "TH1D.h"
#include "DataSet.h"
#include "HistogramPair.h"
#include "HistogramTimeSums.h"
#include "HistogramXY.h"
#include "histogramElecLayers.h"
#include "FitSet.h"
#include "Event.h"
#include "PitchPropSet.h"
#include "HistElecDifferences.h"


TTree* readWriteTree(TTree* tree);
DataSet* loadFromTree(TTree* tree);
void loadFromTreeDataSet(TTree* tree, DataSet* data);
TH1D* plotTimeSpectra(TTree* tree);
void plotTimeSpectraDS(DataSet* data, HistogramPair Hists);
void constructEvents(DataSet* data);
void calculateTimeSums(DataSet* data, HistogramTimeSums timesums);
void plotTimeSums(HistogramTimeSums timesums);
void checkTimeSums(DataSet* data, FitSet fits);
void identifyAndTime(DataSet* data);
void selectPosIonElec(DataSet* data);
void checkReconstructable(DataSet* data);
PitchPropSet calculatePitchProp();
DataSet* sortReconData(DataSet* data, int reconTriplesCount);
void convertLayerPosition(DataSet* reconData, PitchPropSet Pitches);
void convertCartesianPosition(DataSet* reconData, HistogramXY *XYpositions);
void histogramXYPositions(DataSet *reconData, HistogramXY *XYpositions);
void histogramElectronLayers(DataSet *reconData, HistogramElecLayers UVWlayers);
void differenceOfLayers(DataSet* reconData);
HistogramDIFF histogramElecLayerDiff(DataSet *reconData);