#include "GElight.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GELight::GELight()
{
	LightType = GE_LIGHT_DIRECTIONAL;
	CutOff = cosf(glm::radians(25.0f));
	DiffuseColor = { 1.0f, 1.0f, 1.0f };
	AmbientColor = { 1.0f, 1.0f, 1.0f };
	SpecularColor = { 1.0f, 1.0f, 1.0f };
	Ambient = 0.05f;
	ShadowMapSize = 1024;

	ShadowMapFBO = new GEFBO(ShadowMapSize, ShadowMapSize);

	Intensity = 1.0f;
}


GELight::~GELight()
{

}

