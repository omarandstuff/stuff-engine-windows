#include "GE3Dobject.h"

GE3DObject::GE3DObject()
{
	// Identity all transformations
	m_translationMatrix = m_rotationMatrix = m_scaleMatrix = m_orbitMatrix = FinalMatrix = glm::mat4(1.0f);

	// Matrix order multiplication.
	m_reverse = false;

	// Auto updateable
	GEUpdateCaller::sharedInstance()->addUpdateableSelector(this);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::update(float time)
{
	if (m_translationChanged)
	{
		m_translationMatrix = glm::translate(glm::mat4(1.0f), Position * (m_reverse ? -1.0f : 1.0f));
		MatrixChanged = true;
	}

	if (m_rotationChanged)
	{
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x * (m_reverse ? -1.0f : 1.0f)), { 1.0f, 0.0f, 0.0f });
		m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(Rotation.y * (m_reverse ? -1.0f : 1.0f)), { 0.0f, 1.0f, 0.0f });
		m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(Rotation.z * (m_reverse ? -1.0f : 1.0f)), { 0.0f, 0.0f, 1.0f });
		MatrixChanged = true;
	}

	if (m_scaleChanged)
	{
		m_scaleMatrix = glm::scale(Scale * (m_reverse ? -1.0f : 1.0f));
		MatrixChanged = true;
	}

	if (m_orbitChanged)
	{
		m_orbitMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(Orbit.x * (m_reverse ? -1.0f : 1.0f)), { 1.0f, 0.0f, 0.0f });
		m_orbitMatrix = glm::rotate(m_orbitMatrix, glm::radians(Orbit.y * (m_reverse ? -1.0f : 1.0f)), { 0.0f, 1.0f, 0.0f });
		m_orbitMatrix = glm::rotate(m_orbitMatrix, glm::radians(Orbit.z * (m_reverse ? -1.0f : 1.0f)), { 0.0f, 0.0f, 1.0f });
		MatrixChanged = true;
	}

	if (MatrixChanged)
	{
		if(m_reverse)
			FinalMatrix = m_rotationMatrix * m_scaleMatrix * m_translationMatrix * m_orbitMatrix;
		else
			FinalMatrix = m_orbitMatrix * m_translationMatrix * m_scaleMatrix * m_rotationMatrix;
	}

	if (Parent)
	{
		if (Parent->MatrixChanged)
		{
			if (m_reverse)
				FinalMatrix *= Parent->FinalMatrix;
			else
				FinalMatrix = Parent->FinalMatrix * FinalMatrix;
		}
			
	}
}

void GE3DObject::preUpdate()
{

}

void GE3DObject::posUpdate()
{
	m_translationChanged = false;
	m_rotationChanged = false;
	m_scaleChanged = false;
	m_orbitChanged = false;
	MatrixChanged = false;
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Manipulation ------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::setPosition(glm::vec3 position)
{
	Position = position;
	m_translationChanged = true;
}

void GE3DObject::setRotation(glm::vec3 rotation)
{
	Rotation = rotation;
	m_rotationChanged = true;
}

void GE3DObject::setScale(glm::vec3 scale)
{
	Scale = scale;
	m_scaleChanged = true;
}

void GE3DObject::setOrbit(glm::vec3 orbit)
{
	Orbit = orbit;
	m_orbitChanged = true;
}