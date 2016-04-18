#pragma once 
#include "stdafx.h"
#include <vector>
#include "Hit.h"
#include "LayerHit.h"
#include "Constants.h"
#include "MCPTDiff.h"


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
	void storeMCPTDiff(ParticleID particle, double timediff);
	Hit* mcp;
	vector<double> u1;
	vector<double> u2;
	vector<double> v1;
	vector<double> v2;
	vector<double> w1;
	vector<double> w2;
	//time relative to positron
	// for positron hits this will be zero  
	//assuming positron is first hit on the detector
	//vector<MCPTDiff> pos;
	//vector<MCPTDiff> ion;
	//vector<MCPTDiff> other;
	//vector<MCPTDiff> elec;

	vector<MCPTDiff> reltimediff;

};
