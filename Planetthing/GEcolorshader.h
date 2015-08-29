#pragma once

#include "GEshader.h"

class GEColorShader : public GEShader
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEColorShader* sharedInstance();
private:
	GEColorShader() { loadShaderWithFileName(L"Shaders/color_shader", GE_BUFFER_MODE_POSITION); setUpSahder(); };
	GEColorShader(GEColorShader const&) = delete;
	void operator=(GEColorShader const&) = delete;

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	glm::mat4* ModelViewProjectionMatrix;
	GEMaterial* Material;

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

};