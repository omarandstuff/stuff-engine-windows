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
protected:
	glm::mat4 m_finalMatrix;
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_orbit;
	glm::vec3 m_scale;
	glm::vec3 m_lookAt;
	bool m_matrixChanged;
	GE3DObject* m_parent;

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);
	void preUpdate();
	void posUpdate();

	// -------------------------------------------- //
	// ------------ Getters / Setters ------------- //
	// -------------------------------------------- //
public:
	glm::vec3& position();
	glm::vec3& orientation();
	glm::vec3& scale();
	glm::vec3& orbit();
	glm::vec3& lookAt();
	glm::mat4& modelMatrix();
	GE3DObject* parent();

	void position(glm::vec3 position);
	void orientation(glm::vec3 orientation);
	void scale(glm::vec3 scale);
	void orbit(glm::vec3 orbit);
	void lookAt(glm::vec3 lookat);
	void modelMatrix(glm::mat4& matrix);
	void parent(GE3DObject* parent);

	void useLookAt(bool value);
	bool useLookAt();

	// -------------------------------------------- //
	// ------------ Protected members ------------- //
	// -------------------------------------------- //
protected:
	glm::mat4 m_translationMatrix;
	glm::mat4 m_orientationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_orbitMatrix;
	bool m_positionChanged;
	bool m_orientationChanged;
	bool m_scaleChanged;
	bool m_orbitChanged;
	bool m_lookAtChanged;
	bool m_useLookAt;
	bool m_reverse;
	bool m_parentChanged;

	// -------------------------------------------- //
	// --------------- 16B aligment --------------- //
	// -------------------------------------------- //
public:
	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
};
