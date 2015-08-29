#include "GEview.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GEView::GEView()
{
	// Get the shaders.
	m_blinnPhongShader = GEBlinnPhongShader::sharedInstance();
	m_textureShader = GETextureShader::sharedInstance();
	m_colorShader = GEColorShader::sharedInstance();
	m_depthShader = GEDepthShader::sharedInstance();

	// Full Screen
	m_fullScreen = GEFullScreen::sharedInstance();
}


GEView::~GEView()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEView::render()
{
	glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, 1.0f);

	for (vector<GELight*>::iterator light = m_lights.begin(); light != m_lights.end(); light++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, (*light)->ShadowMapFBO->FrameBufferID);
		glViewport(0, 0, (*light)->ShadowMapFBO->Width, (*light)->ShadowMapFBO->Height);
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 matrix = glm::ortho(-60.0f, 60.0f, -60.0f, 60.0f, 1.0f, 200.0f) * glm::lookAt((*light)->Position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_depthShader->ModelViewProjectionMatrix = &matrix;

		(*light)->LightModelViewProjectionMatrix = matrix;

		// Draw back faces.
		glCullFace(GL_FRONT);

		// Render depth of object.
		for (map<wstring, GELayer*>::iterator layer = Layers.begin(); layer != Layers.end(); layer++)
			layer->second->render(GE_RENDER_MODE_DEPTH);
	}

	// To screen render.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 1280, 720);

	glm::mat4 matrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f) * glm::lookAt(glm::vec3(0.0f, 90.0f, 120.0f), glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m_blinnPhongShader->ModelViewProjectionMatrix = &matrix;
	m_blinnPhongShader->Lights = &m_lights;
	m_colorShader->ModelViewProjectionMatrix = &matrix;

	// Render normal objects;
	for (map<wstring, GELayer*>::iterator layer = Layers.begin(); layer != Layers.end(); layer++)
		layer->second->render(GE_RENDER_MODE_NORMAL);

}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Layers ----------------------------------- //
// ------------------------------------------------------------------------------ //

GELayer* GEView::addLayerWithName(wstring name)
{
	if (Layers[name] != 0) return 0;

	GELayer* newLayer = new GELayer;
	newLayer->Name = name;

	Layers[name] = newLayer;

	return newLayer;
}

void GEView::addLayerWithLayer(GELayer* layer)
{
	GELayer* currentLayer = Layers[layer->Name];
	if (currentLayer == 0)
		Layers[layer->Name] = layer;
}

GELayer* GEView::getLayerWithName(wstring name)
{
	return Layers[name];
}

void GEView::removeLayerWithName(wstring name)
{
	Layers.erase(name);
}

void GEView::removeLayer(GELayer* layer)
{
	Layers.erase(layer->Name);
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Lights ----------------------------------- //
// ------------------------------------------------------------------------------ //

void GEView::addLight(GELight* light)
{
	m_lights.push_back(light);
}

void GEView::removeLight(GELight* light)
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

void GEView::cleanLights()
{
	m_lights.clear();
}