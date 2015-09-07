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
	glm::vec3 Direction;
	glm::vec3 Rotation;
	glm::vec3 Scale;
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

	// -------------------------------------------- //
	// ------------ Protected members ------------- //
	// -------------------------------------------- //
protected:
	glm::mat4 m_translationMatrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_lookAtMatrix;
	bool m_translationChanged;
	bool m_rotationChanged;
	bool m_scaleChanged;
	bool m_lookAtChanged;
	bool m_matrixChanged;

	// -------------------------------------------- //
	// --------------- 16B aligment --------------- //
	// -------------------------------------------- //
public:
	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
};
