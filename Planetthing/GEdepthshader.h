#pragma once

#include "GEshader.h"

class GEDepthShader : public GEShader
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEDepthShader* sharedInstance();
private:
	GEDepthShader() { loadShaderWithFileName(L"Shaders/depth_shader", GE_BUFFER_MODE_POSITION); setUpSahder(); };
	GEDepthShader(GEDepthShader const&) = delete;
	void operator=(GEDepthShader const&) = delete;

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	glm::mat4* ModelMatrix;
	glm::mat4* ViewProjectionMatrix;

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

