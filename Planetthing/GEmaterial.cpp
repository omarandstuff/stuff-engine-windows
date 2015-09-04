#include "GEmaterial.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GEMaterial::GEMaterial()
{
	TextureCompression = { 1.0f, 1.0f };
	DiffuseColor = { 0.92f, 0.97f, 1.0f };

	AmbientColor = { 0.92f, 0.97f, 1.0f };
	SpecularColor = { 1.0f, 1.0f, 1.0f };
	Shininess = 8.0f;
	Opasity = 1.0f;
}

GEMaterial::~GEMaterial()
{

}
