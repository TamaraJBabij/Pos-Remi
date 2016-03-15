#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "TTree.h"

// Root does histogram DataSet as there is poor vector intergration
// will try writing data to a new tree with time converted from comSTOP mode and in ns from bins. 
// Will then attempt to histogram

DataSetTree* readWriteTree(TTree* tree) {
	//READ TREE
	//define the variables to hold the read values
	int rawGroupNumber, rawChannel, rawBins;
	//Set up the tree to store values from each entry of the raw data tree
	tree->SetBranchAddress("RawGroupNumber", &rawGroupNumber);
	tree->SetBranchAddress("RawChannel", &rawChannel);
	tree->SetBranchAddress("RawTime", &rawBins);

	//WRITE TREE
	void DataSetTree(){
		//create a tree file tree1.root - create the file, the Tree and a few branches
		int groupNumber, channel, bins;
		TFile f("DataSetTree.root", "recreate");
		TTree tds("tds", "simple tree that stores raw data");
		Int_t GroupNumber, Channel;
		Double_t Time;
	}
	

	//Establish data container variables
	Group* currentGroup = NULL;
	DataSet* data = new DataSet();

	int N = (int)tree->GetEntries();

	//This will loop through all of the entries in the tree
	for (int i = 0; i < N; i++) {
		tree->GetEntry(i);

		if (currentGroup == NULL) {
			//remember the first group
			currentGroup = new Group(groupNumber);
		}

		else if (groupNumber != currentGroup->getId()) {
			data->addGroup(currentGroup);
			currentGroup = new Group(groupNumber);
		}


	}
	return data;
}

/*FIRST ENTRY: make a new group and remember group id
NEW ID: store current group into dataset, make a new group and remember group ID
SAME ID: nothing

ALL 3: add hit to current group*/