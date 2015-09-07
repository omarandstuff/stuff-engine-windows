#pragma once

#include "GEprimitIve.h"

class GECube : public GEPrimitive
{
public:
	GECube(float width, float height, float depth, unsigned int segments_x, unsigned segments_y, unsigned int segments_z);
	~GECube();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float width, float height, float depth, unsigned int segments_x, unsigned segments_y, unsigned int segments_z);

	// -------------------------------------------- //
	// -------------- Private memvers ------------- //
	// -------------------------------------------- //
private:
	void createPlane(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin, glm::vec3 direction, unsigned int vertexOffset, unsigned int indexOffset);
};