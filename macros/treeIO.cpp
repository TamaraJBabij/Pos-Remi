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

		switch (channel) {
		case CFG_CHANNEL_POS_CP2:
			h.channel = ChannelID::mcp;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_U1_S:
			h.channel = ChannelID::u1;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_U2_S:
			h.channel = ChannelID::u2;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_V1_s:
			h.channel = ChannelID::v1;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_V2_S:
			h.channel = ChannelID::v2;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_W1_S:
			h.channel = ChannelID::w1;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_POS_W2_S:
			h.channel = ChannelID::w2;
			h.detector = DetectorID::pos;
			break;
		case CFG_CHANNEL_ELEC_CP2:
			h.channel = ChannelID::mcp;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_U1_S:
			h.channel = ChannelID::u1;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_U2_S:
			h.channel = ChannelID::u2;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_V1_s:
			h.channel = ChannelID::v1;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_V2_S:
			h.channel = ChannelID::v2;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_W1_S:
			h.channel = ChannelID::w1;
			h.detector = DetectorID::neg;
			break;
		case CFG_CHANNEL_ELEC_W2_S:
			h.channel = ChannelID::w2;
			h.detector = DetectorID::neg;
			break;
		}




    	currentGroup->addHit(h);
    }
}

/*FIRST ENTRY: make a new group and remember group id
NEW ID: store current group into dataset, make a new group and remember group ID
SAME ID: nothing

ALL 3: add hit to current group*/