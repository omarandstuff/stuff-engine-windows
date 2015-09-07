#include "GE3Dobject.h"

GE3DObject::GE3DObject()
{
	// Identity all transformations
	m_translationMatrix = m_rotationMatrix = m_scaleMatrix = m_lookAtMatrix = FinalMatrix = glm::mat4(1.0f);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::update(float time)
{
	if (m_translationChanged)
	{
		m_translationMatrix = glm::translate(glm::mat4(1.0f), Position);
		m_translationChanged = false;
		m_matrixChanged = true;
	}
	if (m_rotationChanged)
	{
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f });
		m_rotationMatrix = glm::rotate(m_rotationMatrix, Rotation.y, { 0.0f, 1.0f, 0.0f });
		m_rotationMatrix = glm::rotate(m_rotationMatrix, Rotation.z, { 0.0f, 0.0f, 1.0f });
		m_rotationChanged = false;
		m_matrixChanged = true;
	}
	if (m_scaleChanged)
	{
		m_scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);
		m_scaleChanged = false;
		m_matrixChanged = true;
	}
	if (m_matrixChanged)
	{
		FinalMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;
		m_matrixChanged = false;
	}
}

void GE3DObject::preUpdate()
{

}

void GE3DObject::posUpdate()
{

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
