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

//selects out events with a pos, ion and elec 
//(still need to make sure elec and pos have enough info to reconstruct position)
//if group has more than 1 pos, elec or ion no good
// if group has any other unident particles then no good
 
void selectPosIonElec(DataSet* data) {
	// want to index number of particles and bool triple for each each group
	for (Group* g : *data) {
		double PosCheck = 0;
		double ElecCheck = 0;
		double IonCheck = 0;
		double UnidentCheck = 0;
		for (Event e : g->events) {
			//index particle ids
			switch (e.reltimediff) {

			}	
		}
	}
}