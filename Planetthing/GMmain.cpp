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
	model->RenderBoundingBox = true;
	animation->addSelector(model);

	GELight* light = new GELight;
	//light.LightType = GE_LIGHT_SPOT;
	light->Position = { -100.0f, 60.0f, 10.0f };
	//light.Direction = GLKVector3Make(0.0f, 30.0f, 0.0f);
	light->Intensity = 1.0f;
	light->CastShadows = true;

	view = new GEView;
	view->BackgroundColor = color_banana;

	view->addLight(light);

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
	m_screenWidth = width;
	m_screenHeight = height;
	view->layout(width, height);
}