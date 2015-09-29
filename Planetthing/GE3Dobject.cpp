#include "GE3Dobject.h"

GE3DObject::GE3DObject()
{
	// Identity all transformations
	m_translationMatrix = m_orientationMatrix = m_scaleMatrix = m_orbitMatrix = m_finalMatrix = m_localMatrix = glm::mat4(1.0f);

	// Matrix order multiplication.
	m_reverse = false;

	// Auto updateable
	GEUpdateCaller::sharedInstance()->addUpdateableDelegate(this);

	// Properties syntetis
	ModelMatrix.syntetize(this, &GE3DObject::getModelMatrix, &GE3DObject::setModelMatrix);
	Position.syntetize(this, &GE3DObject::getPosition, &GE3DObject::setPosition);
	Orientation.syntetize(this, &GE3DObject::getOrientation, &GE3DObject::setOrientation);
	Scale.syntetize(this, &GE3DObject::getScale, &GE3DObject::setScale);
	Orbit.syntetize(this, &GE3DObject::getOrbit, &GE3DObject::setOrbit);
	LookAt.syntetize(this, &GE3DObject::getLookAt, &GE3DObject::setLookAt);
	Parent.syntetize(this, &GE3DObject::getParent, &GE3DObject::setParent);
	UseLookAt.syntetize(this, &GE3DObject::getUseLookAt, &GE3DObject::setUseLookAt);

	m_isKinematic = true;
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::update(float time)
{
	if (!m_isKinematic)
	{
		if (RigidBody->isActive())
		{
			btTransform trans;
			btScalar matrix[16];

			MotionState->getWorldTransform(trans);
			trans.getOpenGLMatrix(matrix);

			btQuaternion rotation = trans.getRotation();
			glm::quat rot = glm::make_quat(&rotation.getX());

			m_orientationMatrix = glm::toMat4(rot);

			m_finalMatrix = glm::make_mat4(matrix) * glm::scale(m_scale * (m_reverse ? -1.0f : 1.0f));

			MatrixChanged = true;
		}
	}
	else
	{
		if (m_positionChanged)
		{
			m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position * (m_reverse ? -1.0f : 1.0f));
			MatrixChanged = true;
		}

		if (m_orientationChanged)
		{
			m_orientationMatrix = glm::mat4(glm::quat(glm::vec3(glm::radians(m_orientation.x), glm::radians(m_orientation.y), glm::radians(m_orientation.z)) * (m_reverse ? -1.0f : 1.0f)));
			MatrixChanged = true;
		}

		if (m_scaleChanged)
		{
			m_scaleMatrix = glm::scale(m_scale * (m_reverse ? -1.0f : 1.0f));
			MatrixChanged = true;
		}

		if (m_orbitChanged)
		{
			m_orientationMatrix = glm::mat4(glm::quat(glm::vec3(glm::radians(m_orbit.x), glm::radians(m_orbit.y), glm::radians(m_orbit.z)) * (m_reverse ? -1.0f : 1.0f)));
			MatrixChanged = true;
		}

		if (MatrixChanged)
		{
			if (m_reverse)
				m_localMatrix = m_orientationMatrix * m_scaleMatrix * m_translationMatrix * m_orbitMatrix;
			else
				m_localMatrix = m_orbitMatrix * m_translationMatrix * m_scaleMatrix * m_orientationMatrix;
		}

		if (m_parent)
		{
			if (m_reverse)
				m_finalMatrix = m_localMatrix * glm::inverse((glm::mat4&)m_parent->ModelMatrix);
			else
				m_finalMatrix = (glm::mat4&)m_parent->ModelMatrix * m_localMatrix;
		}
		else
		{
			m_finalMatrix = m_localMatrix;
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
// ----------------------------------- Rigidbody -------------------------------- //
// ------------------------------------------------------------------------------ //

void GE3DObject::makeCubeRigidBody(float width, float height, float depth, bool kinematic)
{
	btCollisionShape* shape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
	m_isKinematic = kinematic;

	btVector3 inertia(0, 0, 0);
	btScalar mass = 0;
	glm::quat orientation = glm::quat(glm::vec3(glm::radians(m_orientation.x), glm::radians(m_orientation.y), glm::radians(m_orientation.z)));
	
	if (!kinematic)
	{
		shape->calculateLocalInertia(1, inertia);
		mass = 1;
	}

	MotionState = new btDefaultMotionState(btTransform(btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w), btVector3(m_position.x, m_position.y, m_position.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, MotionState, shape, inertia);
	rigidBodyCI.m_restitution = 0.5f;
	rigidBodyCI.m_friction = 0.1f;
	RigidBody = new btRigidBody(rigidBodyCI);
}

void GE3DObject::makeSphereRigidBody(float radious, bool kinematic)
{
	btCollisionShape* shape = new btSphereShape(radious);
	m_isKinematic = kinematic;

	btVector3 inertia(0, 0, 0);
	btScalar mass = 0;
	glm::quat orientation = glm::quat(glm::vec3(glm::radians(m_orientation.x), glm::radians(m_orientation.y), glm::radians(m_orientation.z)));

	if (!kinematic)
	{
		shape->calculateLocalInertia(1, inertia);
		mass = 1;
	}

	MotionState = new btDefaultMotionState(btTransform(btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w), btVector3(m_position.x, m_position.y, m_position.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, MotionState, shape, inertia);
	rigidBodyCI.m_restitution = 0.5f;
	rigidBodyCI.m_friction = 0.1f;
	RigidBody = new btRigidBody(rigidBodyCI);
}

void GE3DObject::makePlaneRigidBody(glm::vec3 direction)
{
	m_isKinematic = true;
	btVector3 inertia(0, 0, 0);
	btCollisionShape* shape = new btStaticPlaneShape(btVector3(direction.x, direction.y, direction.z), 1);
	MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(m_position.x, m_position.y, m_position.z)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, MotionState, shape, inertia);
	rigidBodyCI.m_restitution = 0.5f;
	rigidBodyCI.m_friction = 0.1f;
	RigidBody = new btRigidBody(rigidBodyCI);
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Manipulation ------------------------------- //
// ------------------------------------------------------------------------------ //

glm::vec3& GE3DObject::getPosition()
{
	return m_position;
}

void GE3DObject::setPosition(glm::vec3& value)
{
	m_position = value;
	m_positionChanged = true;
}

glm::vec3& GE3DObject::getOrientation()
{
	return m_orientation;
}

void GE3DObject::setOrientation(glm::vec3& value)
{
	m_orientation = value;
	m_orientationChanged = true;
}

glm::vec3& GE3DObject::getScale()
{
	return m_scale;
}

void GE3DObject::setScale(glm::vec3& value)
{
	m_scale = value;
	m_scaleChanged = true;
}

glm::vec3& GE3DObject::getOrbit()
{
	return m_orbit;
}

void GE3DObject::setOrbit(glm::vec3& value)
{
	m_orbit = value;
	m_orbitChanged = true;
}

glm::vec3& GE3DObject::getLookAt()
{
	return m_lookAt;
}

void GE3DObject::setLookAt(glm::vec3& value)
{
	m_lookAt = value;
	m_lookAtChanged = true;
}


glm::mat4& GE3DObject::getModelMatrix()
{
	return m_finalMatrix;
}

void GE3DObject::setModelMatrix(glm::mat4& value)
{
	m_finalMatrix = value;
	MatrixChanged = true;
}


GE3DObject* GE3DObject::getParent()
{
	return m_parent;
}

void GE3DObject::setParent(GE3DObject* value)
{
	m_parent = value;
	m_parentChanged;
}

bool GE3DObject::getUseLookAt()
{
	return m_useLookAt;
}

void GE3DObject::setUseLookAt(bool value)
{
	m_useLookAt = value;
	m_lookAtChanged = true;
}
