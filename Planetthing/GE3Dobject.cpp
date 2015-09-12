#include "GE3Dobject.h"

GE3DObject::GE3DObject()
{
	// Identity all transformations
	m_translationMatrix = m_orientationMatrix = m_scaleMatrix = m_orbitMatrix = m_finalMatrix = glm::mat4(1.0f);

	// Matrix order multiplication.
	m_reverse = false;

	// Auto updateable
	GEUpdateCaller::sharedInstance()->addUpdateableDelegate(this);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::update(float time)
{
	if (m_positionChanged)
	{
		m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position * (m_reverse ? -1.0f : 1.0f));
		m_matrixChanged = true;
	}

	if (m_orientationChanged)
	{

		m_matrixChanged = true;
	}

	if (m_scaleChanged)
	{
		m_scaleMatrix = glm::scale(m_scale * (m_reverse ? -1.0f : 1.0f));
		m_matrixChanged = true;
	}

	if (m_orbitChanged)
	{

		m_matrixChanged = true;
	}

	if (m_matrixChanged)
	{
		if(m_reverse)
			m_finalMatrix = m_orientationMatrix * m_scaleMatrix * m_translationMatrix * m_orbitMatrix;
		else
			m_finalMatrix = m_orbitMatrix * m_translationMatrix * m_scaleMatrix * m_orientationMatrix;
	}

	if (m_parent)
	{
		if (m_parent->m_matrixChanged)
		{
			if (m_reverse)
				m_finalMatrix *= m_parent->m_finalMatrix;
			else
				m_finalMatrix = m_parent->m_finalMatrix* m_finalMatrix;
		}
			
	}
}

void GE3DObject::preUpdate()
{

}

void GE3DObject::posUpdate()
{
	m_positionChanged = false;
	m_orientationChanged = false;
	m_scaleChanged = false;
	m_orbitChanged = false;
	m_lookAtChanged = false;
	m_matrixChanged = false;
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Manipulation ------------------------------- //
// ------------------------------------------------------------------------------ //

glm::vec3& GE3DObject::position()
{
	return m_position;
}

glm::vec3& GE3DObject::orientation()
{
	return m_orientation;
}

glm::vec3& GE3DObject::scale()
{
	return m_scale;
}

glm::vec3& GE3DObject::orbit()
{
	return m_orbit;
}

glm::vec3& GE3DObject::lookAt()
{
	return m_lookAt;
}

glm::mat4& GE3DObject::modelMatrix()
{
	return m_finalMatrix;
}

GE3DObject* GE3DObject::parent()
{
	return m_parent;
}

bool GE3DObject::useLookAt()
{
	return m_useLookAt;
}

void GE3DObject::position(glm::vec3 position)
{
	m_position = position;
	m_positionChanged = true;
}

void GE3DObject::orientation(glm::vec3 orientation)
{
	m_orientation = orientation;
	m_orientationChanged = true;
}

void GE3DObject::scale(glm::vec3 scale)
{
	m_scale = scale;
	m_scaleChanged = true;
}

void GE3DObject::orbit(glm::vec3 orbit)
{
	m_orbit = orbit;
	m_orbitChanged = true;
}

void GE3DObject::lookAt(glm::vec3 lookat)
{
	m_lookAt = lookat;
	m_lookAtChanged = true;
}

void GE3DObject::modelMatrix(glm::mat4& matrix)
{
	m_finalMatrix = matrix;
}

void GE3DObject::parent(GE3DObject* parent)
{
	m_parent = parent;
	m_parentChanged = true;
}

void GE3DObject::useLookAt(bool value)
{
	m_lookAtChanged = !(value == m_useLookAt);
	m_useLookAt = value;
}
