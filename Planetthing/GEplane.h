#pragma once

#include "GErenderable.h"

class GEPlane : public GERenderable
{
public:
	GEPlane();
	GEPlane(float width, float height, GE_DIRECTION direction, unsigned int segment_w, unsigned int segment_h);
	~GEPlane();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	wstring FileName;
	bool Ready;
	bool RenderBoundingBox;
	GEMaterial Material;

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
public:
	void generate(float width, float height, GE_DIRECTION direction, unsigned int segment_w, unsigned int segment_h);

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render(GE_RENDER_MODE mode);

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
private:
	void generateBuffers();

private:
	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	float* m_vertexBuffer;
	unsigned int* m_indexBuffer;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;

};
