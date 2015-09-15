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
	//light->LightType = GE_LIGHT_POINT;
	//light->position({ -10.0f, 6.0f, 1.0f });
	//light->Direction = { 0.0f, 30.0f, 0.0f };
	light->Intensity = 1.0f;
	light->Ambient = 0.2f;
	light->CastShadows = true;

	//GELight* light2 = new GELight;
	//light2.LightType = GE_LIGHT_SPOT;
	//light2->Position = { -0.0f, 60.0f, -10.0f };
	//light2.Direction = GLKVector3Make(0.0f, 30.0f, 0.0f);
	//light2->Intensity = 1.0f;
	//light2->CastShadows = true;

	view = new GEView;
	view->BackgroundColor = color_black;
	//view->Camera.position({ 0.0, 4.0f, 12.0f });
	//view->Camera.orientation({ -2.0f, 0.0f, 0.0f });

	view->addLight(light);
	//view->addLight(light2);

	plane = new GEPlane(38.0f, 26.0f, 10, 10);
	plane->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/Test2.jpg");
	plane->Material.SpecularColor = { 0.1f, 0.1f, 0.1f };

	sphere = new GESphere(1.0f, 4);
	sphere->Material.DiffuseColor = color_greenyellow;
	sphere->Material.Shininess = 1024.0f;
	sphere->Wireframe = false;
	sphere->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	sphere->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");

	cube = new GECube(2.0f, 2.0f, 2.0f, 1, 1, 1);
	cube->Material.DiffuseColor = color_greenyellow;
	cube->Material.Shininess = 1024.0f;
	cube->Wireframe = false;
	cube->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
	cube->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");
	//cube->position({ 0.0f, 20.0f, 0.0f });
	//cube->setScale({ 0.0f, 0.0f, 0.0f });

	//cube->parent(sphere);

	fullScreen = GEFullScreen::sharedInstance();
	fullScreen->TextureID = light->ShadowMapFBO->DepthTextureID;

	GELayer* layer = view->addLayerWithName(L"Layer1");
	//layer->addObject(model);
	layer->addObject(plane);
	layer->addObject(sphere);
	layer->addObject(cube);

	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));

	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	fallShape = new btSphereShape(1.0f);

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBodyCI.m_restitution = 0.6f;

	groundRigidBody = new btRigidBody(groundRigidBodyCI);

	dynamicsWorld->addRigidBody(groundRigidBody);

	fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));

	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBodyCI.m_restitution = 0.6f;
	fallRigidBodyCI.m_friction = 0.3f;

	fallRigidBody = new btRigidBody(fallRigidBodyCI);

	dynamicsWorld->addRigidBody(fallRigidBody);


	cubeShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

	cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0.5, 15, 0)));

	cubeShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMotionState, cubeShape, fallInertia);
	cubeRigidBodyCI.m_restitution = 0.6f;
	cubeRigidBodyCI.m_friction = 0.3f;

	cubeRigidBody = new btRigidBody(cubeRigidBodyCI);

	//cubeRigidBody->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));

	dynamicsWorld->addRigidBody(cubeRigidBody);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::update(float time)
{
	static float angle = 0.0f;

	angle += time / 2.0f;

	//light->position(glm::vec3(25.0f * glm::cos(angle), 10.0f, 25.0f * glm::sin(angle)));

	dynamicsWorld->stepSimulation(time, 5);

	btTransform trans;
	fallRigidBody->getMotionState()->getWorldTransform(trans);

	btScalar matrix[16];

	trans.getOpenGLMatrix(matrix);
	btQuaternion rotation = trans.getRotation();

	glm::quat rot = glm::make_quat(&rotation.getX());


	//sphere->modelMatrix(glm::make_mat4(matrix));
	//sphere->m_rotationMatrix = glm::toMat4(rot);


	cubeRigidBody->getMotionState()->getWorldTransform(trans);

	trans.getOpenGLMatrix(matrix);

	rotation = trans.getRotation();
	rot = glm::make_quat(&rotation.getX());

	//cube->modelMatrix(glm::make_mat4(matrix));
	//cube->m_rotationMatrix = glm::toMat4(rot);


	

	//cube->setRotation({ 90.0f * glm::sin(angle), 0.0f, 0.0f });
	//cube->setOrbit({ 0.0f, 0.0f, 90.0f * glm::cos(angle) });
	//sphere->setPosition({ 0.0f, 10.0f * glm::sin(angle), 0.0f });

	
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

	//plane->position({ (-factorL + factorR) * 50.0f, 0.0f, 0.0f });
}

void GMMain::xBoxControllerStickChange(GE_INPUT_XBOX stick, int player, float xAxis, float yAxis)
{
	//if(stick == GE_INPUT_XBOX_LEFT_STICK)
		//plane->position({ xAxis * 50.0f, 0.0f, yAxis * 50.0f });

	//if (stick == GE_INPUT_XBOX_RIGHT_STICK)
		//plane->orientation({ xAxis * 50.0f, 0.0f, yAxis * 50.0f });
}

// ------------------------------------------------------------------------------ //
// -------------------------------- Mouse events -------------------------------- //
// ------------------------------------------------------------------------------ //

void GMMain::mouseMove(float coordX, float coordY)
{

}

void GMMain::mouseChange(float deltaX, float deltaY)
{
	//glm::vec3 rotation = view->Camera.orientation();

	//rotation.x -= deltaY / 4.0f;
	//rotation.y -= deltaX / 4.0f;

	//view->Camera.orientation(rotation);
}
