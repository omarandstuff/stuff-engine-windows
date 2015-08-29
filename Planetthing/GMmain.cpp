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
	animation->addSelector(model);

	view = new GEView;
	view->BackgroundColor = { 1.0f, 0.5f, 0.1f };

	GELayer* layer = view->addLayerWithName(L"Layer1");
	layer->addObject(model);
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
	view->render();
}

void GMMain::layout(int width, int height)
{
	glViewport(0, 0, width, height);
}