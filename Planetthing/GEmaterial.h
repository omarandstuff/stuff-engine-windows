#pragma once

#include "GEtexture.h"

class GEMaterial
{
	// -------------------------------------------- //
	// -------------- Initialization -------------- //
	// -------------------------------------------- //
public:
	GEMaterial();
	~GEMaterial();

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	glm::vec2 TextureCompression;
	GETexture* DiffuseMap;
	GETexture* SpecularMap;
	glm::vec3 AmbientColor;
	glm::vec3 DiffuseColor;
	glm::vec3 SpecularColor;
	float Shininess;
	float Opasity;

};
