#include "Hit.h"
#include "Event.h"

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