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
// All Timesums are summed for each possible combination in each associated event. 

HistogramTimeSums checkTimeSums(DataSet* data) {

	HistogramTimeSums timesums;
	timesums.layer_upos = new TH1D("upos", "TimeSum upos layer", 200, 0, 1000);
	timesums.layer_vpos = new TH1D("vpos", "TimeSum vpos layer", 200, 0, 1000);
	timesums.layer_wpos = new TH1D("wpos", "TimeSum wpos layer", 200, 0, 1000);
	timesums.layer_uneg = new TH1D("uneg", "TimeSum uneg layer", 200, 0, 1000);
	timesums.layer_vneg = new TH1D("vneg", "TimeSum vneg layer", 200, 0, 1000);
	timesums.layer_wneg = new TH1D("wneg", "TimeSum wneg layer", 200, 0, 1000);
	//Shared ptr, stops memory leaks
	//timesums.test = std::make_shared<TH1D>("wneg", "TimeSum wneg layer", 200, 0, 1000);
	//For each associated event in the group (where group is a 32 micros window)
	//Sum each possible combination of wires that make up the layers to produce timesums for each layer
	for (Group* g : *data) {
		for (Event e : g->events) {
			//positive detector layer hits
			if (e.mcp->detector == pos) {
				for (double u1tdiff : e.u1) {
					for (double u2tdiff : e.u2) {
						timesums.layer_upos->Fill(u1tdiff + u2tdiff);
					}
				}
				for (double v1tdiff : e.v1) {
					for (double v2tdiff : e.v2) {
						timesums.layer_vpos->Fill(v1tdiff + v2tdiff);
					}
				}
				for (double w1tdiff : e.w1) {
					for (double w2tdiff : e.w2) {
						timesums.layer_wpos->Fill(w1tdiff + w2tdiff);
					}
				}
			}
			//negeative detector layer hits
			if (e.mcp->detector == neg) {
				for (double u1tdiff : e.u1) {
					for (double u2tdiff : e.u2) {
						timesums.layer_uneg->Fill(u1tdiff + u2tdiff);
					}
				}
				for (double v1tdiff : e.v1) {
					for (double v2tdiff : e.v2) {
						timesums.layer_vneg->Fill(v1tdiff + v2tdiff);
					}
				}
				for (double w1tdiff : e.w1) {
					for (double w2tdiff : e.w2) {
						timesums.layer_wneg->Fill(w1tdiff + w2tdiff);
					}
				}
			}
		}
	}
	return timesums;
}
