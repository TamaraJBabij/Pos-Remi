#pragma once
#include "PitchData.h"
#include <vector>
#include "Constants.h"

//struct to store the pitch propogation values to be used
//to get X Y position info

using namespace std;

class PitchPropSet {
private:
	vector<PitchPropData> posPitch;
	vector<PitchPropData> negPitch;
public:
	PitchPropSet();
	void setPitchProp(Layer layer, Charge charge, double peak, double error, double sigma);
	PitchPropData getPitchProp(Layer layer, Charge charge);
};
