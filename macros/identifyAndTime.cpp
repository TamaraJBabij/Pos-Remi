#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "Event.h"
#include "stdafx.h"
#include "configparticletimes.h"
#include "Hit.h"
#include <vector>


//takes timedifferences of MCP hits for each event wqithin a group
//identifies particle and stores in MCPTDiff double
//stored is the particleID and timedifference relative to positron

void identifyAndTime(DataSet* data) {
	for (Group* g : *data) {
		for (Event e : g->events) {
			//find positron first
			//identify particle, if detector neg, electron (possibly for function)
			for (e.mcp->detector == pos) {
				if (e.mcp->time < POS_TIME_MAX && e.mcp->time > POS_TIME_MIN) {

				}
			}
		}
	}
}