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

	animation = new GEAnimation(L"resources/models/bob lamp/bob_lamp.md5anim");
	animation->play();
	model = new GEAnimatedModel(L"resources/models/bob lamp/bob_lamp.md5mesh");
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::update(float time)
{

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
	model->render(GE_RENDER_MODE_NORMAL);
}

void GMMain::layout(int width, int height)
{
	glViewport(0, 0, width, height);
}