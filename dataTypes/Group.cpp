//Stores hits and relevant information into a group, group identified by group number
//Raw data goes in, group comes out, you cant explain that

#include <vector>
#include <string>
#include "Hit.h"
#include "Group.h"
#include "TObject.h" 


//required for compatibility with root:
ClassImp(Group);

//constructor where id is passed in as group number from raw tree
Group::Group(int _id)
{
    id = _id;
}
Group::Group(){}
//destructor
Group::~Group()
{
}

//gets ID of current group
int Group::getId(){
	return id;
}

//stores a hit object in the set of raw data.
//parsing in tree of data, and storing that in a vector of hits in each group
void Group::addHit(Hit h)
{
	rawData.push_back(h);
}


vector<Hit>* Group::getHits(){
	return &rawData;
}

