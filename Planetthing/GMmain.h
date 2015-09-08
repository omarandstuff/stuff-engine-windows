#pragma once

#include "GEinput.h"
#include "GEanimatedmodel.h"
#include "GEplane.h"
#include "GEsphere.h"
#include "GEcube.h"
#include "GEview.h"

class GMMain : public GEUpdateProtocol, public GERenderProtocol, public GEInputXBoxControllerProtocol
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


	// -------------------------------------------- //
	// ---------- Xbox Controller Events ---------- //
	// -------------------------------------------- //
	void xBoxControllerButtonDown(GE_INPUT button, int player);
	void xBoxControllerButtonUp(GE_INPUT button, int player);
	void xBoxControllerPullTriguer(GE_INPUT trgger, int player, float value);
	void xBoxControllerMoveStick(GE_INPUT stick, int player, float xAxis, float yAxis);

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
private:
	unsigned int m_screenWidth, m_screenHeight;

	GEAnimation* animation;
	GELight* light;
	GEAnimatedModel* model;
	GEPlane* plane;
	GESphere* sphere;
	GECube* cube;
	GEView* view;
	GECamera* camera;
	GEFullScreen* fullScreen;

};
