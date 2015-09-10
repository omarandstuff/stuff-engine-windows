#pragma once

#include "GEcommon.h"
#include "GEupdatecaller.h"

class GE3DObject : public GEUpdateProtocol
{
public:
	GE3DObject();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	glm::mat4 FinalMatrix;
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Orbit;
	glm::vec3 Scale;
	bool MatrixChanged;
	GE3DObject* Parent;

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);
	void preUpdate();
	void posUpdate();

	// -------------------------------------------- //
	// -------------- Manipulation ---------------- //
	// -------------------------------------------- //
public:
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	void setOrbit(glm::vec3 orbit);

	// -------------------------------------------- //
	// ------------ Protected members ------------- //
	// -------------------------------------------- //
public:
	glm::mat4 m_translationMatrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_orbitMatrix;
	bool m_translationChanged;
	bool m_rotationChanged;
	bool m_scaleChanged;
	bool m_orbitChanged;
	bool m_reverse;

	// -------------------------------------------- //
	// --------------- 16B aligment --------------- //
	// -------------------------------------------- //
public:
	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
};
