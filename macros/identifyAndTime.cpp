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
					//this should be positron
					//save timediff and particleid as positron
					//should save mcp time as pos time to minus other particle mcp times from
					double postime = 0;
					void storeMCPTDiff(ParticleID pos, double postime);
					//now go through all other event mcp times and identify and find rel pos time
					for (Event e : g->events) {
						//not sure how to exclude the current pos event
						//do many switch?
						if (e.mcp->detector == pos) {
							//is it a pos, ion1 ion2 or other
							// not sure if switch is best solution as if nto any of these label it other
							switch (e.mcp->time) {
								case 
							}
						}
						else if (e.mcp->detector == neg) {
							//must be an electron
							ParticleID particle = electron;

						}

					}
				}
			}
		}
	}
}