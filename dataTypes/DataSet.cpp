#include "DataSet.h"
#include <vector>

//required for compatibility with root:
ClassImp(DataSet);
 
//code for the constructor
DataSet::DataSet(){

}

//code for the destructor
DataSet::~DataSet(){

}


//stores a hit object in the set of raw data.
//parsing in tree of data, and storing that in a vector of hits in each group
void DataSet::addGroup(Group* g)
{
	data.push_back(g);
}

//as defined in header file (see comments for explanation)
// when using an object as a data container end and begin functions must exist (in c++)
// allows looping through trhe dataset which loops through the groups in the vector
vector<Group*>::iterator begin(){
	return data.begin()
}
vector<Group*>::iterator end(){
	return data.end()
}
