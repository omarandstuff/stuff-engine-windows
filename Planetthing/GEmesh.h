#pragma once

#include "GEmaterial.h"
#include "GEtriangle.h"
#include "GEjoint.h"
#include "GEframe.h"

class GEMesh
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GEMaterial* Material;
	vector<GEVertex*> Vertices;
	vector<GEtriangle*> Triangles;
	vector<GEWight*> Weights;

	// -------------------------------------------- //
	// -------- Generate - Compute Vertices ------- //
	// -------------------------------------------- //
public:
	void generateBuffers();
	void matchMeshWithFrame(GEFrame* frame);

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render(GLenum mode);

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
private:
	float* m_vertexBuffer;
	unsigned int* m_indexBuffer;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_indexBufferID;

};
