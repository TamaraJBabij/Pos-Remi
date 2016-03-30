#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Event.h"
#include "stdafx.h"
#include "HistogramTimeSums.h"
#include "Hit.h"
#include <vector>

using namespace std;

//Checks time sums for each layer. 
// split histograms for each layer by dector id
// All

HistogramTimeSums checkTimeSums(DataSet* data) {

	HistogramTimeSums timesums;
	timesums.layer_upos = new TH1D("upos", "TimeSum upos layer", 200, 0, 1000);
	timesums.layer_vpos = new TH1D("vpos", "TimeSum vpos layer", 200, 0, 1000);
	timesums.layer_wpos = new TH1D("wpos", "TimeSum wpos layer", 200, 0, 1000);
	timesums.layer_uneg = new TH1D("uneg", "TimeSum uneg layer", 200, 0, 1000);
	timesums.layer_vneg = new TH1D("vneg", "TimeSum vneg layer", 200, 0, 1000);
	timesums.layer_wneg = new TH1D("wneg", "TimeSum wneg layer", 200, 0, 1000);

	for (Group* g : *data) {
		for (Event e : g->events) {
			if (e.mcp->detector == pos) {
				for (double u1tdiff : e.u1) {
					for (double u2tdiff : e.u2) {
						timesums.layer_upos->Fill(u1tdiff + u2tdiff);
					}
				}
			}
		}
	}
	return timesums;
}
