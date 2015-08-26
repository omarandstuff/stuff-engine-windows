#pragma once

#include "GEcommon.h"

class GEJoint
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	wstring Name;
	GEJoint* Parent;
	glm::vec3 Position;
	glm::quat Orientation;

private:

};
