#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Event.h"
#include "stdafx.h"
#include "HistogramTimeSums.h"
#include "Hit.h"
#include <vector>
#include <TTree.h>
#include "configlayers.h"
#include <TFile.h>

using namespace std;

//Checks timesums for each layer
// if timesums not within 2 sigma of peak given by fitting, bad timesums

void checkTimeSums(DataSet* data, TTree* treeTS) {
	//READ TREE
	//define the variables to hold the read values
	Double_t layer, peak, sigma, error;
	//tree->SetBranchAddress("Name of Column", &Set name of pointer);
	treeTS->SetBranchAddress("Layer", &layer);
	treeTS->SetBranchAddress("Peak", &peak);
	treeTS->SetBranchAddress("Sigma", &sigma);
	treeTS->SetBranchAddress("Error", &error);

	//Fills tree
	int N = (int)treeTS->GetEntries();

	//need to store thresholds
	// 2 sigma for each layer

	//check errors of fits, cout error if error of fits over threshold
	//error for each layer compared to errormax in configlayers 


	//for (Group* g : *data) {
		//for (Event e : g->events) {
			//positive detector layer hits
			//if (e.mcp->detector == pos) {
				//for (double u1tdiff : e.u1) {
					//for (double u2tdiff : e.u2) {
						//double uTS = u1tdiff + u2tdiff;
						//compares timesum for layer against the fitted timesum 2sigma
						//if within this +/- 2 sigma then the layer times will be stored in a paired object 
						//for (TTree layer : treeTS) {
							//if (uTS) {
								//At this point it should check against the thhreshold for the timesum
						//}
						//}
							
					//}
				//}
			//}
		//}
	//}
};