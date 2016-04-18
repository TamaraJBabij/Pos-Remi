#pragma once
#include "stdafx.h"
#include "Hit.h"
#include "group.h"
#include "Constants.h"


// stores the relative (to the positron hit) timing and mcp info

struct MCPTDiff {
	ParticleID particle;
	double timediff;
};