#pragma once

#include "GE3Dobject.h"

class GECamera : public GE3DObject
{
public:
	GECamera();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	float Zoom;
	float ViewWidth;
	float ViewHeight;
	float Near;
	float Far;
	GE_CAMERA_TYPE CameraType;
	glm::mat4 ProjectionMatrix;

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);

	// -------------------------------------------- //
	// -------------- Manipulation ---------------- //
	// -------------------------------------------- //
public:
	void setZoom(float zoom);
	void setViewSize(float width, float height);

	// -------------------------------------------- //
	// -------------- Private members ------------- //
	// -------------------------------------------- //
private:
	bool m_projectionChange;
};

