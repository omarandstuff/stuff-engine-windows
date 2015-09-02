#pragma once

#include "GEprimitive.h"

class GESphere : public GEPrimitive
{
public:
	GESphere(float radious, unsigned int segments_u, unsigned int segments_v);
	~GESphere();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float radious, unsigned int segments_u, unsigned int segments_v);
};
