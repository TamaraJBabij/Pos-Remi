#include "DataSet.h"

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
