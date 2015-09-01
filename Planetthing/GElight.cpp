#include "GElight.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GELight::GELight()
{
	LightType = GE_LIGHT_DIRECTIONAL;
	CutOff = cosf(glm::radians(25.0f));
	DiffuseColor = { 1.0f, 0.9f, 0.7f };
	AmbientColor = { 0.88f, 0.95f, 1.0f };
	SpecularColor = { 1.0f, 1.0f, 1.0f };
	Ambient = 0.65f;
	ShadowMapSize = 4096;

	ShadowMapFBO = new GEFBO(ShadowMapSize, ShadowMapSize);

	Intensity = 1.0f;
}


GELight::~GELight()
{

}

