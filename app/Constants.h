#pragma once
#include <vector>

using namespace std;

enum Layer {
	u,
	v,
	w
};

enum Charge {
	positive,
	negative
};


struct Constants {
	static const vector<Layer> layers;
	static const vector<Charge> charges;
};