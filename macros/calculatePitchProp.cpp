#include <iostream>
#include "DataSet.h"
#include "Group.h"
#include "Hit.h"
#include "Event.h"
#include "stdafx.h"
#include "LayerLengthsConfig.h"
#include <vector>
#include "Constants.h"
#include "MCPTDiff.h"
#include "FitSet.h"
#include "FitData.h"
#include "PitchPropSet.h"
#include "PitchData.h"


//caluculates pitch propogation required for reconstruction of coordinates
PitchPropSet* calculatePitchProp(FitSet fits) {
	// rough calculation for pitch propogation
	//need to getFits to make info public
	double upospitch;
	double vpospitch;
	double wpospitch;
	double unegpitch;
	double vnegpitch;
	double wnegpitch;

	PitchPropSet* Pitches;

	//pitch prop for positive detector, u layer
	FitData uposfit = fits.getFit(u, positive);
	upospitch = LENGTH_pU / uposfit.peak;
	//pitch prop for positive detector, v layer
	FitData vposfit = fits.getFit(v, positive);
	vpospitch = LENGTH_pV / vposfit.peak;
	//pitch prop for positive detector, w layer
	FitData wposfit = fits.getFit(w, positive);
	wpospitch = LENGTH_pW / wposfit.peak;
	//pitch prop for negative detector, u layer
	FitData unegfit = fits.getFit(u, negative);
	unegpitch = LENGTH_eU / unegfit.peak;
	//pitch prop for negative detector, v layer
	FitData vnegfit = fits.getFit(v, negative);
	vnegpitch = LENGTH_eV / vnegfit.peak;
	//pitch prop for negative detector, w layer
	FitData wnegfit = fits.getFit(w, negative);
	wnegpitch = LENGTH_eW / wnegfit.peak;
	Pitches->setPitchProp(positive, upospitch, vpospitch, wpospitch);
	Pitches->setPitchProp(negative, unegpitch, vnegpitch, wnegpitch);
	return Pitches;

}