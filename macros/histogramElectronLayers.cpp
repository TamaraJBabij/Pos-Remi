#include "stdafx.h"
#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <TH2D.h>
#include "histogramElecLayers.h"
#include "DataSet.h"
#include "Group.h"

// takes the X,Y positions and makes a 2D histogram for each detector
// hist for positrons, ions and electrons separately

void histogramElectronLayers(DataSet *reconData, HistogramElecLayers UVWlayers) {
	//sort for particle type using 
	//Particle is subset of event and contains time and x, y
	

	for (Group* g : *reconData) {
		if (g->electron.xy_uv == true) {
			UVWlayers.UVlayers->Fill(g->electron.x_uv, g->electron.y_uv);
		}
		if (g->electron.xy_uw == true) {
			UVWlayers.UWlayers->Fill(g->electron.x_uw, g->electron.y_uw);
		}
		if (g->electron.xy_vw == true) {
			UVWlayers.VWlayers->Fill(g->electron.x_vw, g->electron.y_vw);
		}
	}
}