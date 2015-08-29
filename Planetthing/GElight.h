#pragma once

#include "GEcommon.h"
#include "GEfbo.h"

class GELight
{
public:
	GELight();
	~GELight();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GE_LIGHT_TYPE LightType;
	glm::vec3  Position;
	glm::vec3 Direction;
	float CutOff;
	glm::vec3  DiffuseColor;
	glm::vec3  AmbientColor;
	glm::vec3  SpecularColor;
	float Intensity;
	float Ambient;
	bool CastShadows;
	glm::mat4 LightModelViewProjectionMatrix;
	GEFBO* ShadowMapFBO;
	GLint ShadowMapSize;
};
