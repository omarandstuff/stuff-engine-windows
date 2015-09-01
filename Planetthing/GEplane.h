#pragma once

#include "GEprimitive.h"

class GEPlane : public GEPrimitive
{
public:
	GEPlane(float width, float height, unsigned int segment_w, unsigned int segment_h);
	~GEPlane();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float width, float height, unsigned int segment_w, unsigned int segment_h);

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
};
