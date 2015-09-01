#pragma once

#include "GEprimitive.h"

class GESphere : public GEPrimitive
{
	GESphere(float radious, unsigned int segments);
	~GESphere();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float radious, unsigned int segments);

};

