#pragma once
#include "stdafx.h"
#include "Hit.h"
#include "group.h"

// stores the relative (to the positron hit) timing and mcp info

struct MCPTDiff {
	DetectorID detector;
	double timediff;
};