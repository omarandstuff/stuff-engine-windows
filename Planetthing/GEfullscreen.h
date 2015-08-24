#pragma once
#include "GEcommon.h"
#include "GEfullscreenshader.h"

class GEFullScreen
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEFullScreen* sharedInstance();
private:
	GEFullScreen() { createFullScreenVO(); m_fullScreenShader = GEFullScreenShader::sharedInstance(); };
	GEFullScreen(GEFullScreen const&) = delete;
	void operator=(GEFullScreen const&) = delete;

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render();

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	GLuint TextureID;

	// -------------------------------------------- //
	// ------------- private members -------------- //
	// -------------------------------------------- //
private:
	void createFullScreenVO();

private:
	GEFullScreenShader* m_fullScreenShader;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;
};