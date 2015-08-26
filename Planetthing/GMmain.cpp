#include "GMmain.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GMMain* GMMain::sharedInstance()
{
	static GMMain sharedInstance;

	return &sharedInstance;
}

GMMain::GMMain()
{
	// Updatecaller starts here.
	GEUpdateCaller::sharedInstance()->addUpdateableSelector(this);
	GEUpdateCaller::sharedInstance()->addRenderableSelector(this);

	GEAnimation* animation = new GEAnimation(L"resources/models/bob lamp/bob_lamp.md5anim");
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::update(float time)
{
	time;
}

void GMMain::preUpdate()
{

}

void GMMain::posUpdate()
{

}

// ------------------------------------------------------------------------------ //
// ------------------------------- Render - Layout ------------------------------ //
// ------------------------------------------------------------------------------ //

void GMMain::render()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GMMain::layout(int width, int height)
{
	glViewport(0, 0, width, height);
}