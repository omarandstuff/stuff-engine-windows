#pragma once

#include "GEprimitive.h"

class GESphere : public GEPrimitive
{
public:
	GESphere(float radious, unsigned int segments);
	~GESphere();

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
private:
	void generate(float radious, unsigned int segments);

	// -------------------------------------------- //
	// ---------------- Rigidbody ----------------- //
	// -------------------------------------------- //
public:
	void makeRigidBody(bool kinematic = false);

	// -------------------------------------------- //
	// -------------- Private memvers ------------- //
	// -------------------------------------------- //
private:
	void processVertex(float x, float y, float z, unsigned int index, bool lastU, bool lastV);
	void processIndexArea(unsigned int vertexOffset, unsigned int indexOffset, unsigned int areaSegments);

private:
	float m_radious;

};
