#pragma once 
#include "stdafx.h"
#include <vector>
#include "Hit.h"


using namespace std;

class Event
{
private:
	Hit* mcp;
	vector<double> u1;
	vector<double> u2;
	vector<double> v1;
	vector<double> v2;
	vector<double> w1;
	vector<double> w2;
public:
	Event(Hit* mcp);
	void storeHitInfo(double tdiff, ChannelID channel);

};
