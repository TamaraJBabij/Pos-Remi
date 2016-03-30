#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "TTree.h"
#include "TFile.h"
#include "Event.h"
#include "stdafx.h"

// For each "triple event" taken by the logic, layer hits are not stored in order with their mcp hits. 
// Therefore they must be sorted such that the appropriate layer hits can be associated with the appropriate mcpo hit. 
// The criteria for association is chosen to be t_diff < 500 ns

void constructEvents(DataSet* data){
	for (Group* g : *data) {
		for (Hit mcpHit : *g) {
			if (mcpHit.channel == mcp) {
				Event event(&mcpHit);

				for (Hit otherHit : *g) {
					if (otherHit.channel != mcp && otherHit.detector == mcpHit.detector){
						double tdiff = otherHit.time - mcpHit.time;
						if (tdiff < 500 && tdiff>0) {
							//add this tdiff and channel id to the event
							event.storeHitInfo(tdiff, otherHit.channel);
						}
					}
				}

				g->addEvent(event); 
			}
		}
	}
}