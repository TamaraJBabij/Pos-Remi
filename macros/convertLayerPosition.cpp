#include <iostream>
#include "DataSet.h"
#include "stdafx.h"
#include "Group.h"
#include "PitchPropSet.h"
#include "PitchData.h"
#include "math.h"

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
					e->U = (posPitches.uPitchProp / 2)*(e->uPairs.front().line1 - e->uPairs.front().line2) + posPitches.uOffset;
					//cout << e->uPairs.front().line1 << endl;
					//cout << "U layer: " << e->U << endl;
				}
				if (e->vPairs.size() == 1) {
					e->V = (posPitches.vPitchProp / 2)*(e->vPairs.front().line1 - e->vPairs.front().line2) + posPitches.vOffset;
					//cout << "V layer: " << e->V << endl;
				}
				if (e->wPairs.size() == 1) {
					e->W = (posPitches.wPitchProp / 2)*(e->wPairs.front().line1 - e->wPairs.front().line2) + posPitches.wOffset;
					//cout << "W layer: " << e->W << endl;
				}
			}
			if (e->mcp->detector == neg) {
				//see logbook 9 page 114 for diagram of electron detector
				//including gap sizes
				if (e->uPairs.size() == 1) {
					//line2 - line 1 as u1 and u2 reversed (u2 on right hand side) x = righthandside-lefthandside
					double Unogap = (negPitches.uPitchProp / 2)*(e->uPairs.front().line1 - e->uPairs.front().line2) + negPitches.uOffset;
					//cout << "U layer: " << Unogap << endl;
					if (Unogap < 1) {
						e->U = Unogap -(8.407 / 2);
					}
					else {
						e->U = Unogap +(8.407 / 2);
					}
				}
				if (e->vPairs.size() == 1) {
					double Vnogap = (negPitches.vPitchProp / 2)*(e->vPairs.front().line1 - e->vPairs.front().line2) + negPitches.vOffset;
					//cout << "V layer: " << Vnogap << endl;
					if (Vnogap < 0) {
						e->V = Vnogap -(7.283 / 2);
					}
					else {
						e->V = Vnogap +(7.283 / 2);
					}
				}
				if (e->wPairs.size() == 1) {
					//line2 0 lin1 due to electronics configuration
					double Wnogap = (negPitches.wPitchProp / 2)*(e->wPairs.front().line1 - e->wPairs.front().line2) + negPitches.wOffset;
					//cout << "W layer: " << Wnogap << endl;
					if (Wnogap < 0.5) {
						e->W = Wnogap -(7.479 / 2);
					}
					else {
						e->W = Wnogap +(7.479 / 2);
					}
				}
			}
		}
	}
}