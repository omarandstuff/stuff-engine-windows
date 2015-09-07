#pragma once

#include "GEshader.h"

class GEBlinnPhongShader : public GEShader
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEBlinnPhongShader* sharedInstance();
private:
	GEBlinnPhongShader() { loadShaderWithFileName(L"Shaders/blinn_phong_shader", GE_BUFFER_MODE_ALL); setUpSahder(); DiffuceMapEnabled = true; SpecularMapEnabled = true; };
	GEBlinnPhongShader(GEBlinnPhongShader const&) = delete;
	void operator=(GEBlinnPhongShader const&) = delete;

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	glm::mat4* ModelMatrix;
	glm::mat4* ViewProjectionMatrix;
	glm::mat4* NormalMatrix;
	GEMaterial* Material;
	vector<GELight*>* Lights;
	bool DiffuceMapEnabled;
	bool SpecularMapEnabled;

public:
	// -------------------------------------------- //
	// ---------------- Use Program --------------- //
	// -------------------------------------------- //
	void useProgram();

	// -------------------------------------------- //
	// ------------- private members -------------- //
	// -------------------------------------------- //
private:
	void setUpSahder();

private:
	GLint m_uniforms[GE_NUM_UNIFORMS];
	GLint m_lightUniforms[10][GE_NUM_LIGHT_UNIFORMS];
};

