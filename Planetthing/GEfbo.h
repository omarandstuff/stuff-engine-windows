#pragma once

#include "GEopengl.h"

class GEFBO
{
public:
	GEFBO();
	GEFBO(GLsizei width, GLsizei height);
	~GEFBO();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GLuint FrameBufferID;
	GLuint TextureID;
	GLuint DepthTextureID;
	GLsizei Width;
	GLsizei Height;

	// -------------------------------------------- //
	// --------------- FBO Control ---------------- //
	// -------------------------------------------- //
	void generate(GLsizei width, GLsizei height);
};
