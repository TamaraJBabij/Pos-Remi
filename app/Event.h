#pragma once 
#include "stdafx.h"
#include <vector>
#include "Hit.h"
#include "LayerHit.h"
#include "Constants.h"

//stores the associated layer hits for the mcp hit 
//layer hit object - store layer hits with appropriate timesums
//appropriate timesum is defined as nsigma within peak as fitted by gaus

using namespace std;

class Event
{
private:
	vector<LayerHit> uPairs;
	vector<LayerHit> vPairs;
	vector<LayerHit> wPairs;

public:
	Event(Hit* mcp);
	void storeHitInfo(double tdiff, ChannelID channel);
	void storePair(Layer layer, double line1, double line2);
	Hit* mcp;
	vector<double> u1;
	vector<double> u2;
	vector<double> v1;
	vector<double> v2;
	vector<double> w1;
	vector<double> w2;

};
