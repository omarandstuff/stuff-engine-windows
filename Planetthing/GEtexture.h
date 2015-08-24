#pragma once

#include <IL\config.h>
#include <IL\il.h>
#include "GEopengl.h"
#include "GEcommon.h"

class GETexture
{
	// -------------------------------------------- //
	// ----------- Unique Texture Sytem ----------- //
	// -------------------------------------------- //
public:
	static GETexture* textureWithFileName(wstring filename);
	void releaseTexture();
	~GETexture();
private:
	GETexture() {};
	GETexture(GETexture const&) = delete;
	void operator=(GETexture const&) = delete;
private:
	static map<wstring, pair<int, GETexture*>> m_texturesHolder;

public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	GLuint TextureID;
	wstring FileName;
	GLuint Width;
	GLuint Height;

public:
	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
	void loadTextureWithFileName(wstring filename);

private:
	unsigned char* loadImageWithFileName(wstring filename);
	void generateTextureFromPixels(unsigned char* rawPixels);
};
