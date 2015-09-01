#pragma once

#include "GEblinnphongshader.h"
#include "GEtextureshader.h"
#include "GEdepthshader.h"
#include "GEcolorshader.h"

class GERenderable
{
public:
	GERenderable()
	{
		// Get the shaders.
		m_blinnPhongShader = GEBlinnPhongShader::sharedInstance();
		m_textureShader = GETextureShader::sharedInstance();
		m_colorShader = GEColorShader::sharedInstance();
		m_depthShader = GEDepthShader::sharedInstance();

		// Ebanled and Visible by default.
		Enabled = true;
		Visible = true;

		// Wireframe false by default.
		Wireframe = false;
		m_wireframeMaerial.DiffuseColor = color_wheat;

	}

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	bool Visible;
	bool Enabled;
	bool Wireframe;

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	virtual void render(enum GE_RENDER_MODE mode) = 0;

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
protected:
	GEBlinnPhongShader* m_blinnPhongShader;
	GETextureShader* m_textureShader;
	GEDepthShader* m_depthShader;
	GEColorShader* m_colorShader;

	GEMaterial m_wireframeMaerial;
};
