#pragma once

#include "GEupdatecaller.h"
#include "GEanimatedmodel.h"
#include "GEplane.h"
#include "GEview.h"

class GMMain : public GEUpdateProtocol, public GERenderProtocol
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GMMain* sharedInstance();
private:
	GMMain();
	GMMain(GMMain const&) = delete;
	void operator=(GMMain const&) = delete;

	// -------------------------------------------- //
	// --------- Update - Render - Layout --------- //
	// -------------------------------------------- //
public:
	void preUpdate();
	void update(float time);
	void posUpdate();
	void render();
	void layout(int width, int height);

private:
	unsigned int m_screenWidth, m_screenHeight;

	GEAnimation* animation;
	GEAnimatedModel* model;
	GEPlane* plane;
	GEView* view;

};
