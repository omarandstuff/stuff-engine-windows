#include "GE3Dobject.h"

GE3DObject::GE3DObject()
{
	// Identity all transformations
	m_translationMatrix = m_orientationMatrix = m_scaleMatrix = m_orbitMatrix = ModelMatrix = glm::mat4(1.0f);

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
		m_translationMatrix = glm::translate(glm::mat4(1.0f), Position * (m_reverse ? -1.0f : 1.0f));
		MatrixChanged = true;
	}

	if (m_orientationChanged)
	{

		MatrixChanged = true;
	}

	if (m_scaleChanged)
	{
		m_scaleMatrix = glm::scale(Scale * (m_reverse ? -1.0f : 1.0f));
		MatrixChanged = true;
	}

	if (m_orbitChanged)
	{

		MatrixChanged = true;
	}

	if (MatrixChanged)
	{
		if(m_reverse)
			ModelMatrix = m_orientationMatrix * m_scaleMatrix * m_translationMatrix * m_orbitMatrix;
		else
			ModelMatrix = m_orbitMatrix * m_translationMatrix * m_scaleMatrix * m_orientationMatrix;
	}

	if (Parent)
	{
		if (Parent->MatrixChanged)
		{
			if (m_reverse)
				ModelMatrix *= Parent->ModelMatrix;
			else
				ModelMatrix = Parent->ModelMatrix* ModelMatrix;
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
	MatrixChanged = false;
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Manipulation ------------------------------- //
// ------------------------------------------------------------------------------ //

glm::vec3& GE3DObject::getPosition()
{
	return Position;
}

glm::vec3& GE3DObject::getOrientation()
{
	return Orientation;
}

glm::vec3& GE3DObject::getScale()
{
	return Scale;
}

glm::vec3& GE3DObject::getOrbit()
{
	return Orbit;
}

glm::vec3& GE3DObject::getLookAt()
{
	return LookAt;
}

glm::mat4& GE3DObject::getModelMatrix()
{
	return ModelMatrix;
}

void GE3DObject::setPosition(glm::vec3& position)
{
	position = position;
	m_positionChanged = true;
}

void GE3DObject::setOrientation(glm::vec3& orientation)
{
	Orientation = orientation;
	m_orientationChanged = true;
}

void GE3DObject::setScale(glm::vec3& scale)
{
	Scale = scale;
	m_scaleChanged = true;
}

void GE3DObject::setOrbit(glm::vec3& orbit)
{
	Orbit = orbit;
	m_orbitChanged = true;
}

void GE3DObject::setLookAt(glm::vec3& lookat)
{
	LookAt = lookat;
	m_lookAtChanged = true;
}

void GE3DObject::setModelMatrix(glm::mat4& matrix)
{
	ModelMatrix = matrix;
	MatrixChanged = true;
}
