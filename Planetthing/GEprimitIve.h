#pragma once

#include "GErenderable.h"

class GEPrimitive : public GERenderable
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GEMaterial Material;

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render(enum GE_RENDER_MODE mode);

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
protected:
	void generateBuffers();

protected:
	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	float* m_vertexBuffer;
	unsigned int* m_indexBuffer;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;
};

