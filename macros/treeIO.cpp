#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "TTree.h"

//make each group, fill it with hits, add it to the dataset
DataSet loadFromTree(TTree* tree){
	int groupNumber, channel, bins;

	//Set up the tree to store values from each entry of the raw data tree
	tree->SetBranchAddress("GroupNumber",&groupNumber);
	tree->SetBranchAddress("Channel", &channel);
	tree->SetBranchAddress("Time", &bins);

	//Establish data container variables
	Group* currentGroup = NULL;
    DataSet* data = new DataSet();

	int N = (int) tree->GetEntries();

	int a = 3;

	//This will loop through all of the entries in the tree
	for (int i = 0; i < N; i++) {
		tree->GetEntry(i);

    	if(currentGroup==NULL){
    		//remember the first group
            currentGroup = new Group(groupNumber);
    	}
    	else if( groupNumber != currentGroup->getId() ){
    		data->addGroup(currentGroup);
    		currentGroup = new Group(groupNumber);
    	}
    	Hit h;

        //make the Hit object by loading the values from the tree according to the config file





    	currentGroup->addHit(h);
    }
}

/*FIRST ENTRY: make a new group and remember group id
NEW ID: store current group into dataset, make a new group and remember group ID
SAME ID: nothing

ALL 3: add hit to current group*/