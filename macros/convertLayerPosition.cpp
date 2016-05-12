#include <iostream>
#include "DataSet.h"
#include "stdafx.h"
#include "Group.h"
#include "PitchPropSet.h"
#include "PitchData.h"

//converts from timing u1 u2 to U
//uses pitch propogation factor to convert timing info to position info
//stills need to be converted to cartesian after this
void convertLayerPosition(DataSet* reconData, PitchPropSet Pitches) {
	//retrieve pitch propagation calculations
	//these are same for all events/groups
	PitchPropData posPitches = Pitches.getPitchProp(positive);
	PitchPropData negPitches = Pitches.getPitchProp(negative);
	for (Group* g : *reconData) {
		for (Event* e : g->events) {
			if (e->mcp->detector == pos) {
				if (e->uPairs.size() == 1) {
					e->U = (posPitches.ulayer / 2)*(e->uPairs.front().line1 - e->uPairs.front().line1);
				}
				if (e->vPairs.size() == 1) {
					e->V = (posPitches.vlayer / 2)*(e->vPairs.front().line1 - e->vPairs.front().line1);
				}
				if (e->wPairs.size() == 1) {
					e->W = (posPitches.wlayer / 2)*(e->wPairs.front().line1 - e->wPairs.front().line1);
				}
			}
			if (e->mcp->detector == neg) {
				if (e->uPairs.size() == 1) {
					e->U = (negPitches.ulayer / 2)*(e->uPairs.front().line1 - e->uPairs.front().line1);
				}
				if (e->vPairs.size() == 1) {
					e->V = (negPitches.vlayer / 2)*(e->vPairs.front().line1 - e->vPairs.front().line1);
				}
				if (e->wPairs.size() == 1) {
					e->W = (negPitches.wlayer / 2)*(e->wPairs.front().line1 - e->wPairs.front().line1);
				}
			}
		}
	}
}