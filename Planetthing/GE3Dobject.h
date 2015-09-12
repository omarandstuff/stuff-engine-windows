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
	__declspec(property(get = getModelMatrix, put = setModelMatrix)) glm::mat4 ModelMatrix;
	__declspec(property(get = getPosition, put = setPosition)) glm::vec3 Position;
	__declspec(property(get = getOrientation, put = setOrientation)) glm::vec3 Orientation;
	__declspec(property(get = getOrbit, put = setOrbit)) glm::vec3 Orbit;
	__declspec(property(get = getScale, put = setScale)) glm::vec3 Scale;
	__declspec(property(get = getLookAt, put = setLookAt)) glm::vec3 LookAt;
	bool MatrixChanged;
	GE3DObject* Parent;
	bool UseLookAt;

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
private:
	glm::vec3& getPosition();
	void setPosition(glm::vec3& value);

	glm::vec3& getOrientation();
	void setOrientation(glm::vec3& value);

	glm::vec3& getScale();
	void setScale(glm::vec3& value);

	glm::vec3& getOrbit();
	void setOrbit(glm::vec3& value);

	glm::vec3& getLookAt();
	void setLookAt(glm::vec3& value);

	glm::mat4& getModelMatrix();
	void setModelMatrix(glm::mat4& value);

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
