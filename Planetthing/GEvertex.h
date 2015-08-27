#pragma once

#include "GEweigh.h"

class GEVertex
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	unsigned int Index;
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoord;
	vector<GEWight*> Weights;
};
