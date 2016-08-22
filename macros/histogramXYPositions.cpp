#include "stdafx.h"
#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <TH2D.h>
#include "HistogramXY.h"
#include "DataSet.h"
#include "Group.h"

// takes the X,Y positions and makes a 2D histogram for each detector
// hist for positrons, ions and electrons separately

void histogramXYPositions(DataSet *reconData, HistogramXY *XYpositions) {
	//sort for particle type using 
	//Particle is subset of event and contains time and x, y
	

	for (Group* g : *reconData) {
		XYpositions->positronDET->Fill(g->positron.x, g->positron.y);
		XYpositions->electronDET->Fill(g->electron.x, g->electron.y);
		XYpositions->ionDET->Fill(g->ion.x, g->ion.y);
	}
}