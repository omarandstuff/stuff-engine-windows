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
	GEUpdateCaller::sharedInstance()->addUpdateableDelegate(this);
	GEUpdateCaller::sharedInstance()->addRenderableDelegate(this);

	// Input the Xbox Controller to here
	GEInput::sharedInstance()->addXBoxContollerDelegate(this);
	GEInput::sharedInstance()->addMouseDelegate(this);

	//animation = new GEAnimation(L"resources/models/bob lamp/bob_lamp.md5anim");
	//animation->play();
	//model = new GEAnimatedModel(L"resources/models/bob lamp/bob_lamp.md5mesh");
	//model->RenderBoundingBox = true;
	//animation->addDelegate(model);

	//model->setScale({ 0.1f, 0.1f, 0.1f });

	//model = new GEAnimatedModel(L"resources/images/sphere.md5mesh");
	//model->Meshes[0].Material.Shininess = 128.0f;

	light = new GELight;
	light->Intensity = 1.0f;
	light->Ambient = 0.2f;
	light->CastShadows = true;

	view = new GEScene;
	view->BackgroundColor = color_banana;
	view->Camera.Position = glm::vec3(0.0f, 20.0f, 0.0f);
	view->Camera.Orientation = glm::vec3(-90.0f, 0.0f, 0.0f);

	view->addLight(light);

	GELayer* layer = view->addLayerWithName(L"Layer1");

	earth = new GESphere(20.0f, 12);
	earth->Material.DiffuseColor = color_black;
	earth->Material.Shininess = 1024.0f;
	earth->Wireframe = true;
	earth->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	earth->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");
	earth->makeRigidBody(true);
	layer->addObject(earth);


	for (int i = 0; i < 20; i++)
	{
		cubes[i] = new GECube(2.0f, 2.0f, 2.0f, 1, 1, 1);
		cubes[i]->Material.DiffuseColor = color_greenyellow;
		cubes[i]->Material.Shininess = 1024.0f;
		cubes[i]->Wireframe = false;
		cubes[i]->Position = glm::vec3(0.0f, 30, 0.0f);
		cubes[i]->makeRigidBody();
		cubes[i]->RigidBody->setRestitution(0.0f);
		layer->addObject(cubes[i]);
	}

	player = new GECube(2.0f, 2.0f, 2.0f, 1, 1, 1);
	player->Material.DiffuseColor = color_blue_3;
	player->Material.Shininess = 1024.0f;
	player->Wireframe = false;
	player->Position = glm::vec3(1, 40, 0);
	player->makeRigidBody();
	layer->addObject(player);

	view->Camera.Parent = player;
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::update(float time)
{
	// Sun
	static float angle = 0.0f;
	angle += time / 2.0f;
	light->Position = glm::vec3(40.0f * glm::cos(angle), 0.0f, 40.0f * glm::sin(angle));

	view->update(time);
}

void GMMain::preUpdate()
{
	btTransform trans;
	btVector3 direction;

	for (int i = 0; i < 20; i++)
	{
		cubes[i]->MotionState->getWorldTransform(trans);
		direction = trans.getOrigin().normalize() * -9.8f;
		cubes[i]->RigidBody->setGravity(direction);
	}

	player->MotionState->getWorldTransform(trans);
	direction = trans.getOrigin().normalize() * -9.8f;
	player->RigidBody->setGravity(direction);
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

// ------------------------------------------------------------------------------ //
// --------------------------- Xbox Controller Events --------------------------- //
// ------------------------------------------------------------------------------ //
void GMMain::xBoxControllerButtonDown(GE_INPUT_XBOX button, int player)
{

}

void GMMain::xBoxControllerButtonUp(GE_INPUT_XBOX button, int player)
{

}

void GMMain::xBoxControllerTriguerChange(GE_INPUT_XBOX trigger, int player, float value)
{

}

void GMMain::xBoxControllerStickChange(GE_INPUT_XBOX stick, int player, float xAxis, float yAxis)
{
	if (stick == GE_INPUT_XBOX_RIGHT_STICK)
	{
		glm::vec3 rotation = view->Camera.Orientation;

		rotation.x = -90.0f + yAxis * 90.0f;
		rotation.y = xAxis * -90.0f;

		view->Camera.Orientation = rotation;
	}
	if (stick == GE_INPUT_XBOX_LEFT_STICK)
	{

	}
}

// ------------------------------------------------------------------------------ //
// -------------------------------- Mouse events -------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::mouseMove(float coordX, float coordY)
{

}

void GMMain::mouseChange(float deltaX, float deltaY)
{
	
}