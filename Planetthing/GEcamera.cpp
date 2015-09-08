#include "GEcamera.h"

GECamera::GECamera()
{
	// Matrix order multiplication.
	m_reverse = true;

	// First
	m_projectionChange = true;

	// Default perspective
	CameraType = GE_CAMERA_PERSPECTIVE;

	// Near and Far defaults
	Near = 0.1f;
	Far = 1000.0f;

	// Default Width Height
	ViewWidth = ViewHeight = 1.0f;
}


// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GECamera::update(float time)
{
	GE3DObject::update(time);

	if (m_projectionChange)
	{
		if (CameraType == GE_CAMERA_PERSPECTIVE)
		{
			ProjectionMatrix = glm::perspective(glm::radians(45.0f - 45.0f * Zoom), ViewWidth / ViewHeight, Near, Far);
		}
		else
		{
			float factorw = ViewWidth / 2.0f;
			float factorh = ViewHeight / 2.0f;
			ProjectionMatrix = glm::ortho(-factorw + factorw * Zoom, factorw - factorw * Zoom, factorh - factorh * Zoom, -factorh + factorh * Zoom, Near, Far);
		}
		m_projectionChange = false;
	}
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Manipulation ------------------------------- //
// ------------------------------------------------------------------------------ //

void GECamera::setZoom(float zoom)
{
	Zoom = zoom;
	m_projectionChange = true;
}

void GECamera::setViewSize(float width, float height)
{
	ViewWidth = width;
	ViewHeight = height;
	m_projectionChange = true;
}