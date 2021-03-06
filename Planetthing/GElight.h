#pragma once

#include "GEcommon.h"
#include "GE3Dobject.h"
#include "GEfbo.h"

class GELight : public GE3DObject
{
public:
	GELight();
	~GELight();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GE_LIGHT_TYPE LightType;
	float CutOff;
	glm::vec3 Direction;
	glm::vec3  DiffuseColor;
	glm::vec3  AmbientColor;
	glm::vec3  SpecularColor;
	float Intensity;
	float Ambient;
	bool CastShadows;
	glm::mat4 ShadowMapViewProjectionMatrix;
	GEFBO* ShadowMapFBO;
	GLint ShadowMapSize;
};
