#include "stdafx.h"
#include "PitchPropSet.h"
#include <vector>
#include "Constants.h"

PitchPropSet::PitchPropSet() {
	posPitch = vector<PitchPropData>(3, PitchPropData());
	negPitch = vector<PitchPropData>(3, PitchPropData());
}

void PitchPropSet::setPitchProp(Layer layer, Charge charge, double ulayer, double vlayer, double wlayer) {
	PitchPropData data;
	data.ulayer = ulayer;
	data.vlayer = vlayer;
	data.wlayer = wlayer;

	if (charge == positive) {
		posPitch[layer] = data;
	}
	else {
		negPitch[layer] = data;
	}
}

PitchPropData PitchPropSet::getPitchProp(Layer layer, Charge charge) {
	if (charge == positive) {
		return posPitch.at(layer);
	}
	else {
		return negPitch.at(layer);
	}
}