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
	view->BackgroundColor = color_black;
	view->Camera.Position = glm::vec3(0.0, 30.0f, 40.0f);
	view->Camera.Orientation = glm::vec3(-2.0f, 0.0f, 0.0f);

	view->addLight(light);

	GELayer* layer = view->addLayerWithName(L"Layer1");

	earth = new GESphere(20.0f, 12);
	earth->Material.DiffuseColor = color_greenyellow;
	earth->Material.Shininess = 1024.0f;
	earth->Wireframe = true;
	earth->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	earth->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");
	layer->addObject(earth);


	for (int i = 0; i < 200; i++)
	{
		cubes[i] = new GECube(2.0f, 2.0f, 2.0f, 1, 1, 1);
		cubes[i]->Material.DiffuseColor = color_greenyellow;
		cubes[i]->Material.Shininess = 1024.0f;
		cubes[i]->Wireframe = false;
		layer->addObject(cubes[i]);
	}

	//// World
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0f, 0.0f, 0.0f));

	// Earth
	earthShape = new btSphereShape(20);
	btDefaultMotionState* auxMs = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo earthRigidBodyCI(0, auxMs, earthShape, btVector3(0, 0, 0));
	earthRigidBodyCI.m_restitution = 0.6f;
	earthRigidBody = new btRigidBody(earthRigidBodyCI);

	dynamicsWorld->addRigidBody(earthRigidBody);

	btVector3 boxInertia;
	boxshape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	boxshape->calculateLocalInertia(1, boxInertia);

	for (int i = 0; i < 200; i++)
	{
		auxMs = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0.0, 50, 0)));
		btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, auxMs, boxshape, boxInertia);
		cubeRigidBodyCI.m_restitution = 0.7f;
		cubeRigidBodyCI.m_friction = 0.3f;
		boxRigidBodies[i] = new btRigidBody(cubeRigidBodyCI);
		dynamicsWorld->addRigidBody(boxRigidBodies[i]);
	}
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

	dynamicsWorld->stepSimulation(time, 5);
}

void GMMain::preUpdate()
{
	btTransform trans;
	btVector3 direction;
	btRigidBody* current;

	for (int i = 0; i < 200; i++)
	{
		current = boxRigidBodies[i];
		boxRigidBodies[i]->getMotionState()->getWorldTransform(trans);
		direction = trans.getOrigin().normalize() * -9.8f;
		boxRigidBodies[i]->setGravity(direction);
	}
}

void GMMain::posUpdate()
{
	btTransform trans;
	btScalar matrix[16];

	for (int i = 0; i < 200; i++)
	{
		boxRigidBodies[i]->getMotionState()->getWorldTransform(trans);
		trans.getOpenGLMatrix(matrix);
		cubes[i]->ModelMatrix = glm::make_mat4(matrix);
	}
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
	static float factorL = 0.0f;
	static float factorR = 0.0f;
	if (trigger == GE_INPUT_XBOX_LEFT_TRIGGER)
		factorL = value;
	if (trigger == GE_INPUT_XBOX_RIGHT_TRIGGER)
		factorR = value;
}

void GMMain::xBoxControllerStickChange(GE_INPUT_XBOX stick, int player, float xAxis, float yAxis)
{

}

// ------------------------------------------------------------------------------ //
// -------------------------------- Mouse events -------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::mouseMove(float coordX, float coordY)
{

}

void GMMain::mouseChange(float deltaX, float deltaY)
{
	glm::vec3 rotation = view->Camera.Orientation;

	rotation.x -= deltaY / 4.0f;
	rotation.y -= deltaX / 4.0f;

	view->Camera.Orientation = rotation;
}