#pragma once

#include "GEprimitive.h"

class GEPlane : public GEPrimitive
{
public:
	GEPlane(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin = 0.0f, glm::vec3 direction = { 0.0f, 1.0f, 0.0f });
	~GEPlane();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin = 0.0f, glm::vec3 direction = { 0.0f, 1.0f, 0.0f });
};
