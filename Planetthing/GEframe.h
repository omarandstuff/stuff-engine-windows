#pragma once

#include "GEjoint.h"
#include "GEbound.h"

class GEFrame
{
public:
	~GEFrame()
	{
		// Delete every dynmic memory hoint in the hoint vector.
		for (vector<GEJoint*>::iterator it = Joints.begin(); it != Joints.end(); it++)
			delete *it;
	}
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	vector<GEJoint*> Joints;
	GEBound Bounds;

};
