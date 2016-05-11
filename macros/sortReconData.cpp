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
#include "..\app\macros.h"
#include "TripleCheck.h"

using namespace std;
//creates a new dataset with reconstructable data
DataSet* sortReconData(DataSet* data) {
	DataSet* reconData = new DataSet();


	//sort out useful data groups
	for (Group* g : *data) {
		
		if (g->particles.TripleCoinc) {
			 bool recon = true;
			 cout << "recon group" << endl;
			 for (Event e : g->events) {
				 if (e.reconstructInfo == notReconstructable) {
					 recon = false;
					 break;
				 }
			 }
			 //If the group contains reconstructable particles cope over to new dataset
			 if (recon == true) {
				 //stores a pointer to the group
				 //therefore reconData wiull contains pointers to all relevant groups
				 reconData->addGroup(g);
				 cout << "recon group" << endl;
			 }
		}
	}

	return reconData;
}