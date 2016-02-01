#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

//make each group, fill it with hits, add it to the dataset
DataSet loadFromTree(TFile* treeFile){
	//treeReader is a TTreeReader that we will use to get the values from the tree
  	TTreeReader treeReader("T", treeFile);
  	//Set up the readers to get the values from each entry of the raw data tree
    TTreeReaderValue<Int_t> groupNumberReader(treeReader, "GroupNumber");
    TTreeReaderValue<Int_t> channelReader(treeReader, "Channel");
    TTreeReaderValue<Int_t> timeReader(treeReader, "Time");
     //We need to set some things up for the first entry, so we start this as true,
    //and set it to false as soon as we've finished the set up
    bool firstEntry = true;
    Group* currrentGroup=NULL;
    DataSet* data = new DataSet();
    //This will loop through all of the entries in the tree
    while(rawTreeReader.Next()){
    	if(currentGroup==NULL){
    		//remember the first group
            currentGroup = new Group(*groupNumberReader);
    	}
    	else if( *groupNumberReader != currentGroup->getId() ){
    		data->addGroup(currentGroup);
    		currentGroup = new Group(*groupNumberReader);
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