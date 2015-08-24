#pragma once

#include "GEshader.h"

class GEFullScreenShader : public GEShader
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEFullScreenShader* sharedInstance();
private:
	GEFullScreenShader() { loadShaderWithFileName(L"Shaders/fullscreen_shader", GE_BUFFER_MODE_POSITION_TEXTURE); setUpSahder(); };
	GEFullScreenShader(GEFullScreenShader const&) = delete;
	void operator=(GEFullScreenShader const&) = delete;

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	GLuint TextureID;

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
	GLint uniforms[GE_NUM_UNIFORMS];

};