#pragma once

#include "GElayer.h"
#include "GEtextureshader.h"
#include "GEblinnphongshader.h"
#include "GEcolorshader.h"
#include "GEdepthshader.h"
#include "GEfullscreen.h"

class GEView
{
public:
	GEView();
	~GEView();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	glm::vec3 BackgroundColor;
	float Opasity;
	map<wstring, GELayer*> Layers;
	int Width, Height;

	// -------------------------------------------- //
	// ------------------ Layers ------------------ //
	// -------------------------------------------- //
public:

	GELayer* addLayerWithName(wstring name);
	void addLayerWithLayer(GELayer* layer);
	GELayer* getLayerWithName(wstring name);
	void removeLayerWithName(wstring name);
	void removeLayer(GELayer* layer);

	// -------------------------------------------- //
	// ------------------ Lights ------------------ //
	// -------------------------------------------- //
	void addLight(GELight* light);
	void removeLight(GELight* light);
	void cleanLights();

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render();
	void layout(int width, int height);

	// -------------------------------------------- //
	// ------------- Private Members -------------- //
	// -------------------------------------------- //
private:
	GEBlinnPhongShader* m_blinnPhongShader;
	GETextureShader* m_textureShader;
	GEDepthShader* m_depthShader;
	GEColorShader* m_colorShader;

	vector<GELight*> m_lights;

	GEFullScreen* m_fullScreen;
};

