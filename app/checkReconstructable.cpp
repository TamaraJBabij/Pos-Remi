#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "Event.h"
#include "stdafx.h"
#include "configparticletimes.h"
#include <vector>
#include "Constants.h"
#include "MCPTDiff.h"

//ions dont need position info
//any pos or elec need to have atleast two layer hits
//if true assign a bool to event

void checkReconstructable(DataSet* data) {
	//checks has enough layer hits to reconstruct a position
	for (Group* g : *data) {
		for (Event* e : g->events) {
			//index particle ids
			//Want these values to reset for each event, bette rplacement here
			int uCheck = 0;
			int vCheck = 0;
			int wCheck = 0;
			if (e->reltimediff.particle == ion1) {
				//dont need any position info, just need mco hit therefore is reconstructable
				int uSize = e->uPairs.size();
				int vSize = e->vPairs.size();
				int wSize = e->wPairs.size();
				//As vector of layerhits (where layehits contains u1, u2)
				//want vector length of 1!!
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
					e->reconstructInfo = reconstructable;
				}
				else {
					e->reconstructInfo = ionNoPosition;
				}
			}
			if (e->reltimediff.particle == positron) {
				//need to know somehow check that there is atleast two LayerHits 
				//(and in each layer hit there is no more than 1 set)
				//is switch best way of doing this?
				//get vector size, want 2
				//switch (e.uPairs.size())
					//case 2:
					//uCheck++;
					//case >2:
				int uSize = e->uPairs.size();
				int vSize = e->vPairs.size();
				int wSize = e->wPairs.size();
				//As vector of layerhits (where layehits contains u1, u2)
				//want vector length of 1!!
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
					e->reconstructInfo = reconstructable;
				}
				else {
					e->reconstructInfo = notReconstructable;
				}
			}
				if (e->reltimediff.particle == electron) {
					int uSize = e->uPairs.size();
					int vSize = e->vPairs.size();
					int wSize = e->wPairs.size();
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
						e->reconstructInfo = reconstructable;
					}
					else {
						e->reconstructInfo = notReconstructable;
					}
				}
			}
	}
}

