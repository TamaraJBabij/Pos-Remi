#pragma once 
#include "stdafx.h"
#include <vector>
#include "Hit.h"
#include "LayerHit.h"
#include "Constants.h"
#include "MCPTDiff.h"
#include "ReconBool.h"



//stores the associated layer hits for the mcp hit 
//layer hit object - store layer hits with appropriate timesums
//appropriate timesum is defined as nsigma within peak as fitted by gaus


class Event
{
private:


public:
	Event(Hit* mcp);
	void storeHitInfo(double tdiff, ChannelID channel);
	void storePair(Layer layer, double line1, double line2);
	void storeMCPTDiff(ParticleID particle, double timediff);
	//As recon info public
	//void Event::storeReconInfo(bool reconstructable);

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
	vector<LayerHit> uPairs;
	vector<LayerHit> vPairs;
	vector<LayerHit> wPairs;
	
	ReconInfoStruct reconstructInfo;

	//Not actually a relative time difference, need to be changed to absolute timing
	MCPTDiff reltimediff;

	//Particle type, either positron, electron, ion1 (Ar+), ion2 (Ar++) or unknown
	ParticleID particletype;
	//All particle TOF are made relative to the positron
	double timefrompos;
	//Time of the MCP hit in absolute normal time
	//double mcptimeabs;

	// layers
	double U;
	double V;
	double W;

};
