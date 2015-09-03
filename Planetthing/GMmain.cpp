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

	//animation = new GEAnimation(L"resources/models/bob lamp/bob_lamp.md5anim");
	//animation->play();
	//model = new GEAnimatedModel(L"resources/models/bob lamp/bob_lamp.md5mesh");
	//model->RenderBoundingBox = true;
	//animation->addSelector(model);

	GELight* light = new GELight;
	//light.LightType = GE_LIGHT_SPOT;
	light->Position = { -100.0f, 60.0f, 10.0f };
	//light.Direction = GLKVector3Make(0.0f, 30.0f, 0.0f);
	light->Intensity = 1.0f;
	light->CastShadows = true;

	GELight* light2 = new GELight;
	//light2.LightType = GE_LIGHT_SPOT;
	light2->Position = { -0.0f, 60.0f, -10.0f };
	//light2.Direction = GLKVector3Make(0.0f, 30.0f, 0.0f);
	light2->Intensity = 1.0f;
	light2->CastShadows = true;

	view = new GEView;
	view->BackgroundColor = color_black;

	view->addLight(light);
	//view->addLight(light2);

	plane = new GEPlane(380.0f, 260.0f, 10, 10);
	plane->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/Test2.jpg");

	sphere = new GESphere(40.0f, 40, 20);
	sphere->Material.DiffuseColor = color_greenyellow;
	sphere->Wireframe = false;

	GELayer* layer = view->addLayerWithName(L"Layer1");
	//layer->addObject(model);
	//layer->addObject(plane);
	layer->addObject(sphere);
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