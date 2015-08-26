#pragma once

#include "GEjoint.h"
#include "GEbound.h"

class GEFrame
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	vector<GEJoint> Joints;
	GEBound Bound;

};
