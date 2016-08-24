#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "Event.h"
#include "stdafx.h"
#include "configparticletimes.h"
#include <vector>
#include "Constants.h"


//takes timedifferences of MCP hits for each event within a group
//identifies particle and stores in MCPTDiff double
//stored is the particleID and timedifference relative to positron

void identifyAndTime(DataSet* data) {
	for (Group* g : *data) {
		for (Event* e : g->events) {
			//find positron first
			//identify particle, if detector neg, electron (possibly for function)
			// As logic for a mcp pulse with layer info starting the comstop has been removed, 
			// need to sort for only positrons with layer info

			if (e->mcp->detector == pos) {
				if (e->mcp->time < POS_TIME_MAX && e->mcp->time > POS_TIME_MIN) {

					int uSize = e->uPairs.size();
					int vSize = e->vPairs.size();
					int wSize = e->wPairs.size();
					int uCheck = 0; 
					int vCheck = 0;
					int wCheck = 0;
					
					if (uSize == 1) {
						//adds to ucheck +1
						uCheck = 1;
					}
					if (vSize == 1) {
						vCheck = 1;
					}
					if (wSize == 1) {
						wCheck = 1;
					}
					if (uCheck + vCheck + wCheck >= 2) {
						//this should be positron
						//save timediff and particleid as positron
						//should save mcp time as pos time to minus other particle mcp times from
						double reltimezero;
						//sets the time you minus all other particle times from
						reltimezero = e->mcp->time;
						double postime = 0;
						e->storeMCPTDiff(positron, postime);
						e->particletype = positron;
						e->timefrompos = postime;
						//now go through all other event mcp times and identify and find rel pos time
						for (Event* other : g->events) {
							//loops through all events in group g that are NOT the positron
							if (other->mcp != e->mcp) {
								//not sure how to exclude the current pos event
								//do many switch?
								if (other->mcp->detector == pos) {
									//is it a pos, ion1 ion2 or other
									// not sure if switch is best solution as if not any of these label it other
									//switch (other.mcp->time) {
									//case
									//}
									//pehraps better to use if else if else as if nto ion 1 or 2 must be other
									if (other->mcp->time < ION1_TIME_MAX && other->mcp->time > ION1_TIME_MIN) {
										//is Ar+
										double ion1time;
										ion1time = other->mcp->time - reltimezero;
										other->storeMCPTDiff(ion1, ion1time);
										other->particletype = ion1;
										other->timefrompos = ion1time;
									}
									else if (other->mcp->time < ION2_TIME_MAX && other->mcp->time > ION2_TIME_MIN) {
										//is Ar++
										double ion2time;
										ion2time = other->mcp->time - reltimezero;
										other->storeMCPTDiff(ion2, ion2time);
										other->particletype = ion2;
										other->timefrompos = ion2time;
									}
									else
									{
										//must be background (perhaps other positron)
										double unidenttime;
										unidenttime = other->mcp->time - reltimezero;
										other->storeMCPTDiff(unidentified, unidenttime);
										other->particletype = unidentified;
										other->timefrompos = unidenttime;
									}
								}
								else if (other->mcp->detector == neg) {
									//must be an electron
									double electime;
									//find relative time of electron
									electime = other->mcp->time - reltimezero;
									//store relative electron time and particleID
									other->storeMCPTDiff(electron, electime);
									other->particletype = electron;
									other->timefrompos = electime;
								}
							}

						}
						//implemented incase multiple positrons
						//when finds positron stops looping through events in group 
						//(other events associated with positron still looped through)
						break;
					}
				}
			}
		}
	}
}