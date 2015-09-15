#pragma once

#include "GEcommon.h"
#include "GEupdatecaller.h"

class GE3DObject : public GEUpdateProtocol
{
public:
	GE3DObject();

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);
	void preUpdate();
	void posUpdate();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
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
	bool m_parentChanged;
	bool m_useLookAt;
	bool m_reverse;

	glm::mat4 m_finalMatrix;
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_scale;
	glm::vec3 m_orbit;
	glm::vec3 m_lookAt;

	GE3DObject* m_parent;

public:
	bool MatrixChanged;
	Property<GE3DObject, glm::mat4&> ModelMatrix;
	glm::vec3 Position;

private:

	// -------------------------------------------- //
	// ------------ Getters / Setters ------------- //
	// -------------------------------------------- //
private:
	glm::mat4& getModelMatrix();
	void setModelMatrix(glm::mat4& value);

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

	GE3DObject* getParent();
	void setParent(GE3DObject* value);

	bool getUseLookAt();
	void setUseLookAt(bool value);

	// -------------------------------------------- //
	// --------------- 16B aligment --------------- //
	// -------------------------------------------- //
public:
	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
};
