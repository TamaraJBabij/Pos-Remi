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
					e->U = (posPitches.ulayer / 2)*(e->uPairs.front().line1 - e->uPairs.front().line2);
					//cout << e->uPairs.front().line1 << endl;
					//cout << "U layer: " << e->U << endl;
				}
				if (e->vPairs.size() == 1) {
					e->V = (posPitches.vlayer / 2)*(e->vPairs.front().line1 - e->vPairs.front().line2);
					//cout << "V layer: " << e->V << endl;
				}
				if (e->wPairs.size() == 1) {
					e->W = (posPitches.wlayer / 2)*(e->wPairs.front().line1 - e->wPairs.front().line2);
					//cout << "W layer: " << e->W << endl;
				}
			}
			if (e->mcp->detector == neg) {
				if (e->uPairs.size() == 1) {
					//line2 - line 1 as u1 and u2 reversed (u2 on right hand side) x = righthandside-lefthandside
					double Unogap = (negPitches.ulayer / 2)*(e->uPairs.front().line1 - e->uPairs.front().line2);
					//cout << "U layer: " << Unogap << endl;
					if (Unogap <= 0) {
						e->U = Unogap - 4.5;
					}
					else {
						e->U = Unogap + 3.5;
					}
				}
				if (e->vPairs.size() == 1) {
					double Vnogap = (negPitches.vlayer / 2)*(e->vPairs.front().line1 - e->vPairs.front().line2);
					//cout << "V layer: " << Vnogap << endl;
					if (Vnogap <= 0) {
						e->V = Vnogap - 4;
					}
					else {
						e->V = Vnogap + 4;
					}
				}
				if (e->wPairs.size() == 1) {
					double Wnogap = (negPitches.wlayer / 2)*(e->wPairs.front().line1 - e->wPairs.front().line2);
					//cout << "W layer: " << Wnogap << endl;
					if (Wnogap <= 0) {
						e->W = Wnogap -3.5;
					}
					else {
						e->W = Wnogap + 5.5;
					}
				}
			}
		}
	}
}