#include <iostream>
#include "DataSet.h"
#include "stdafx.h"
#include "Group.h"
#include "PitchPropSet.h"
#include "PitchData.h"
#include "math.h"

//since we average over all layer reconstructions, want to make sure the numbers for each UV, UW, VW are simliar

void differenceOfLayers(DataSet* reconData) {
	for (Group* g : *reconData) {
		if (g->electron.x_uv && g->electron.x_uw){
			g->electron.x_uv_uw = g->electron.x_uv - g->electron.x_uw;
			cout << "electron x uv " << g->electron.x_uv << endl;
			cout << "electron x uw " << g->electron.x_uw << endl;
			cout << "electron x uv - uw " << g->electron.x_uv_uw << endl;
		}
	}
	
}