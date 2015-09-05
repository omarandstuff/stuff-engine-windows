#pragma once

#include "GEprimitive.h"

class GESphere : public GEPrimitive
{
public:
	GESphere(float radious, unsigned int segments);
	~GESphere();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float radious, unsigned int segments);

	// -------------------------------------------- //
	// -------------- Private memvers ------------- //
	// -------------------------------------------- //
private:
	void processVertex(float x, float y, float z, float radious, unsigned int index, bool lastU, bool lastV);
	void processIndexArea(unsigned int vertexOffset, unsigned int indexOffset, unsigned int areaSegments);
};
