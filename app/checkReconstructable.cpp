#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "Event.h"
#include "stdafx.h"
#include "configparticletimes.h"
#include <vector>
#include "Constants.h"
#include "MCPTDiff.h"

//ions dont need position info
//any pos or elec need to have atleast two layer hits
//if true assign a bool to event

void checkReconstrutable(DataSet* data) {
	for (Group* g : *data) {
			for (Event e : g->events) {
			//index particle ids
			//Want these values to reset for each event, bette rplacement here
			int uCheck = 0;
			int vCheck = 0;
			int wCheck = 0;
			if (e.reltimediff.particle == ion1) {
				//dont need any position info, just need mco hit therefore is reconstructable
				e.storeReconBool(true);
			}
			if (e.reltimediff.particle == positron) {
				//need to nwo somehow check that ther eis atleast to LayerHits 
				//(and in each layer hit there is no more than 1 set)
				//is switch best way of doing this?
				//get vector size, want 2
				
			}
			if (e.reltimediff.particle == electron) {

			}
		}
	}
}

