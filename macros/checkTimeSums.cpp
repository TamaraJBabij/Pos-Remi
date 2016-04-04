#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Event.h"
#include "stdafx.h"
#include "HistogramTimeSums.h"
#include "Hit.h"
#include <vector>

using namespace std;

//Checks timesums for each layer
// if timesums not within 2 sigma of peak given by fitting, bad timesums

//void checkTimeSums(Dataset* data){}