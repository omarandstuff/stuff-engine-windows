#pragma once

#include "GEupdatecaller.h"
#include "GEtexture.h"
#include "GEanimatedmodel.h"

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

	GEAnimation* animation;
	GEAnimatedModel* model;

};
