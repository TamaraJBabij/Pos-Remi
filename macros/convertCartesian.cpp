#include <iostream>
#include "DataSet.h"
#include "stdafx.h"
#include "Group.h"
#include "PitchPropSet.h"
#include "PitchData.h"
#include "math.h"
#include <TF1.h>
#include <TH2D.h>
#include "HistogramXY.h"

void convertCartesianPosition(DataSet* reconData, HistogramXY *XYpositions) {
	//cout << "convertCartesianPosition" << endl;
	for (Group* g : *reconData) {
		//cout << "Group:" << endl;
		for (Event* e : g->events) {
			if (e->mcp->detector == pos) {
				Particle p;
				p.t = e->reltimediff.timediff;
				p.x = 0.00;
				p.y = 0.00;
				p.r = 0.00;
				p.xy_uv = false;
				p.xy_uw = false;
				p.xy_vw = false;
				int count = 0;
				if (e->uPairs.size() == 1 && e->vPairs.size() == 1) {
					//g->positron = Particle(32,23123,2341)
					p.x_uv = - e->U;
					//p.y = (1 / sqrt(3))*(e->U - 2 * e->V);
					p.y_uv = (1 / sqrt(3))*( e->U - 2 * e->V);
					p.x += p.x_uv;
					p.y += p.y_uv;
					count++;
					p.xy_uv = true;
				}
				else if (e->uPairs.size() == 1 && e->wPairs.size() == 1) {
					p.x_uw = - e->U;
					//p.y_uw = (1 / sqrt(3))*(2 * e->W - e->U);
					p.y_uw = (1 / sqrt(3))*(2 * e->W - e->U);
					p.x += p.x_uw; 
					p.y += p.y_uw;
					count++;
					p.xy_uw = true;
				}
				else if (e->vPairs.size() == 1 && e->wPairs.size() == 1) {
					p.x_vw = - e->V - e->W;
					//p.y_vw = (1 / sqrt(3))*(e->W - e->V);
					p.y_vw = (1 / sqrt(3))*(e->W - e->V);
					p.x += p.x_vw;
					p.y += p.y_vw;
					count++;
					p.xy_vw = true;
				}
				p.x = p.x / count;
				p.y = p.y / count;
				p.r = sqrt(pow(p.x, 2) + pow(p.x, 2));

				switch (e->reltimediff.particle) {
				case positron:
					g->positron = p;
					//cout << " - positron" << " x: " << p.x << " y: " << p.y << endl;
					break;
					//case electron:
						//g->electron = p;
						//cout << " - electron" << " x: " << p.x << " y: " << p.y << endl;
						//break;
				case ion1:
					g->ion = p;
					break;
				}
			}
			else if (e->mcp->detector == neg) {
				Particle p;
				p.t = e->reltimediff.timediff;
				p.x = 0.00;
				p.y = 0.00;
				p.r = 0.00;
				//setting these bools allows for layers to be plotted separately 
				//as the corresponding doubles are set up in the group.h they exist
				//makes hard to sort for UV and VW and UW constructions
				//bools tagged reconstructed events
				p.xy_uv = false;
				p.xy_uw = false;
				p.xy_vw = false;
				int count = 0;
				if (e->uPairs.size() == 1 && e->vPairs.size() == 1) {
					//g->positron = Particle(32,23123,2341)
					//see logbook 9 page 125-126 for why this cartesian conversion is used. 
					//see logbook 9 page 114 for diagram of electron detector
					p.x_uv = e->U;
					p.x += p.x_uv;
					p.y_uv = (1 / sqrt(3))*( - e->U + 2 * e->V);
					p.y += p.y_uv;
					count++;
					p.xy_uv = true;
				}
				if (e->uPairs.size() == 1 && e->wPairs.size() == 1) {
					p.x_uw = e->U;
					p.y_uw = (1 / sqrt(3))*(  2 * e->W + e->U);
					p.x += p.x_uw;
					p.y += p.y_uw;
					count++;
					p.xy_uw = true;
   				}
				if (e->vPairs.size() == 1 && e->wPairs.size() == 1) {
					p.x_vw = e->V - e->W;
					p.y_vw = (1 / sqrt(3))*(e->W + e->V);
					p.x += p.x_vw;
					p.y += p.y_vw;
					count++;
					p.xy_vw = true;
				}
				p.x = p.x / count;
				p.y = p.y / count;
				p.r = sqrt(pow(p.x, 2) + pow(p.x, 2));
				g->electron = p;
			}
		}
		XYpositions->positronDET->Fill(g->positron.x, g->positron.y);
		XYpositions->electronDET->Fill(g->electron.x, g->electron.y);
		XYpositions->ionDET->Fill(g->ion.x, g->ion.y);
	}
}