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

	//model = new GEAnimatedModel(L"resources/images/sphere.md5mesh");
	//model->Meshes[0].Material.Shininess = 128.0f;

	light = new GELight;
	//light->LightType = GE_LIGHT_POINT;
	light->Position = { -100.0f, 60.0f, 10.0f };
	//light->Direction = { 0.0f, 30.0f, 0.0f };
	light->Intensity = 0.8f;
	light->Ambient = 0.4f;
	light->CastShadows = true;

	//GELight* light2 = new GELight;
	//light2.LightType = GE_LIGHT_SPOT;
	//light2->Position = { -0.0f, 60.0f, -10.0f };
	//light2.Direction = GLKVector3Make(0.0f, 30.0f, 0.0f);
	//light2->Intensity = 1.0f;
	//light2->CastShadows = true;

	view = new GEView;
	view->BackgroundColor = color_black;
	view->Camera.setPosition({ 0.0, 40.0f, 120.0f });
	view->Camera.setRotation({ -20.0f, 0.0f, 0.0f });

	view->addLight(light);
	//view->addLight(light2);

	plane = new GEPlane(380.0f, 260.0f, 10, 10);
	plane->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/Test2.jpg");
	plane->Material.SpecularColor = { 0.1f, 0.1f, 0.1f };

	sphere = new GESphere(10.0f, 4);
	sphere->Material.DiffuseColor = color_greenyellow;
	sphere->Material.Shininess = 1024.0f;
	sphere->Wireframe = true;
	sphere->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	sphere->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");

	cube = new GECube(40.0f, 40.0f, 40.0f, 1, 1, 1);
	cube->Material.DiffuseColor = color_greenyellow;
	cube->Material.Shininess = 1024.0f;
	cube->Wireframe = true;
	cube->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	cube->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");
	cube->setPosition({ 0.0f, 20.0f, 0.0f });
	cube->setScale({ 0.5f, 0.5f, 0.5f });

	cube->Parent = sphere;

	fullScreen = GEFullScreen::sharedInstance();
	fullScreen->TextureID = light->ShadowMapFBO->DepthTextureID;

	GELayer* layer = view->addLayerWithName(L"Layer1");
	//layer->addObject(model);
	layer->addObject(plane);
	layer->addObject(sphere);
	layer->addObject(cube);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::update(float time)
{
	static float angle = 0.0f;

	angle += time / 2.0f;

	light->Position = glm::vec3(250.0f * glm::cos(angle), 100.0f, 250.0f * glm::sin(angle));

	cube->setRotation({ 90.0f * glm::sin(angle), 0.0f, 0.0f });
	cube->setOrbit({ 0.0f, 0.0f, 90.0f * glm::cos(angle) });
	sphere->setPosition({ 0.0f, 10.0f * glm::sin(angle), 0.0f });
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
	//fullScreen->render();
}

void GMMain::layout(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	view->layout(width, height);
}