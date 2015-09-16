#include "GEscene.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GEScene::GEScene()
{
	// Get the shaders.
	m_blinnPhongShader = GEBlinnPhongShader::sharedInstance();
	m_textureShader = GETextureShader::sharedInstance();
	m_colorShader = GEColorShader::sharedInstance();
	m_depthShader = GEDepthShader::sharedInstance();

	// Build the physics world.
	m_broadphase = new btDbvtBroadphase();
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_solver = new btSequentialImpulseConstraintSolver;
	DynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	// Standard earth grabity.
	DynamicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));
}


GEScene::~GEScene()
{
	// Delete the physics world objects
	delete m_broadphase;
	delete m_collisionConfiguration;
	delete m_dispatcher;
	delete m_solver;
	delete DynamicsWorld;
}

// ------------------------------------------------------------------------------ //
// -------------------------------- Render / Update ----------------------------- //
// ------------------------------------------------------------------------------ //

void GEScene::update(float time)
{
	// Update the dynamics for thhis frame.
	DynamicsWorld->stepSimulation(time, 5);
}

void GEScene::render()
{
	glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, 1.0f);

	// Calculate every light shadow if it casts them.
	for (vector<GELight*>::iterator light = m_lights.begin(); light != m_lights.end(); light++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, (*light)->ShadowMapFBO->FrameBufferID);
		glViewport(0, 0, (*light)->ShadowMapFBO->Width, (*light)->ShadowMapFBO->Height);
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 matrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 400.0f) * glm::lookAt((glm::vec3&)(*light)->Position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_depthShader->ViewProjectionMatrix = &matrix;

		(*light)->ShadowMapViewProjectionMatrix = matrix;

		// Draw back faces.
		glCullFace(GL_FRONT);

		// Render depth of object.
		for (map<wstring, GELayer*>::iterator layer = Layers.begin(); layer != Layers.end(); layer++)
			layer->second->render(GE_RENDER_MODE_DEPTH);
	}

	// To screen render.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Width, Height);

	// View projection matric based the camera projection and position of this scene.
	glm::mat4 matrix = Camera.ProjectionMatrix * (glm::mat4&)Camera.ModelMatrix;

	// Pass it to the shaders that need it.
	m_blinnPhongShader->ViewProjectionMatrix = &matrix;
	m_blinnPhongShader->Lights = &m_lights;
	m_colorShader->ViewProjectionMatrix = &matrix;

	// Render normal objects;
	for (map<wstring, GELayer*>::iterator layer = Layers.begin(); layer != Layers.end(); layer++)
		layer->second->render(GE_RENDER_MODE_NORMAL);
}

void GEScene::layout(int width, int height)
{
	Width = width;
	Height = height;
	Camera.setViewSize((float)width, (float)height);
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Layers ----------------------------------- //
// ------------------------------------------------------------------------------ //

GELayer* GEScene::addLayerWithName(wstring name)
{
	if (Layers[name] != 0) return 0;

	GELayer* newLayer = new GELayer;
	newLayer->Name = name;

	Layers[name] = newLayer;

	newLayer->DynamicsWorld = DynamicsWorld;

	return newLayer;
}

void GEScene::addLayerWithLayer(GELayer* layer)
{
	GELayer* currentLayer = Layers[layer->Name];
	if (currentLayer == 0)
		Layers[layer->Name] = layer;
}

GELayer* GEScene::getLayerWithName(wstring name)
{
	return Layers[name];
}

void GEScene::removeLayerWithName(wstring name)
{
	Layers.erase(name);
}

void GEScene::removeLayer(GELayer* layer)
{
	Layers.erase(layer->Name);
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Lights ----------------------------------- //
// ------------------------------------------------------------------------------ //

void GEScene::addLight(GELight* light)
{
	m_lights.push_back(light);
}

void GEScene::removeLight(GELight* light)
{
	for (vector<GELight*>::iterator _light = m_lights.begin(); _light != m_lights.end(); _light++)
	{
		if (*_light._Ptr == light)
		{
			m_lights.erase(_light);
			return;
		}
	}
}

void GEScene::cleanLights()
{
	m_lights.clear();
}
