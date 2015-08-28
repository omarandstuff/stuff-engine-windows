#pragma once

#include "GEopengl.h"
#include "GEbound.h"

class GEBoundingBox
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEBoundingBox* sharedInstance();
private:
	GEBoundingBox() { generateBoundingLines(); };
	GEBoundingBox(GEBoundingBox const&) = delete;
	void operator=(GEBoundingBox const&) = delete;

	// -------------------------------------------- //
	// -------------- Render - Update ------------- //
	// -------------------------------------------- //
	public:
	void updateBoundingLines(GEBound* bound);
	void render();

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
private:
	void generateBoundingLines();

private:
	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;
};
