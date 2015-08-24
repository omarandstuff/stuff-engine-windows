#pragma once
#include "GEcommon.h"
#include "GEopengl.h"

class GEFullScreen
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEFullScreen* sharedInstance();
private:
	GEFullScreen() { createFullScreenVO(); };
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
	//GEFullScreenShader* m_fullScreenShader;

	GLuint m_vertexBufferId;
	GLuint m_vertexArrayId;
};