#pragma once

#include "GEshader.h"

class GETextureShader : public GEShader
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GETextureShader* sharedInstance();
private:
	GETextureShader() { loadShaderWithFileName(L"Shaders/texture_shader", GE_BUFFER_MODE_POSITION_TEXTURE); setUpSahder(); };
	GETextureShader(GETextureShader const&) = delete;
	void operator=(GETextureShader const&) = delete;

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