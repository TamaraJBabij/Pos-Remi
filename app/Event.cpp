#include "stdafx.h"
#include "Hit.h"
#include "Event.h"
#include "Constants.h"
#include "MCPTDiff.h"

//constructor mcp is the uniquely associated mcp hit
Event::Event(Hit* _mcp) {
	mcp = _mcp;
}


void Event::storeHitInfo(double tdiff, ChannelID channel) {
	switch (channel) {
	case ChannelID::u1:
		// want to add tdiff to the vector u1
		u1.push_back(tdiff);
		break;
	case ChannelID::u2:
		// want to add tdiff to the vector u1
		u2.push_back(tdiff);
		break;
	case ChannelID::v1:
		// want to add tdiff to the vector u1
		v1.push_back(tdiff);
		break;
	case ChannelID::v2:
		// want to add tdiff to the vector u1
		v2.push_back(tdiff);
		break;
	case ChannelID::w1:
		// want to add tdiff to the vector u1
		w1.push_back(tdiff);
		break;
	case ChannelID::w2:
		// want to add tdiff to the vector u1
		w2.push_back(tdiff);
		break;
	}
}

void Event::storePair(Layer layer, double hit1, double hit2){
	LayerHit pair;
	pair.line1 = hit1;
	pair.line2 = hit2;
	switch (layer) {
	case Layer::u:
		uPairs.push_back(pair);
		break;
	}
}


void Event::storeMCPTDiff(ParticleID particle, DetectorID detector, double timediff) {

}