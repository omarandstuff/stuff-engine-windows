#pragma once

#include "GElayer.h"
#include "GEtextureshader.h"
#include "GEblinnphongshader.h"
#include "GEcolorshader.h"
#include "GEdepthshader.h"
#include "GEfullscreen.h"
#include "GEcamera.h"

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
	GECamera Camera;

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

	// -------------------------------------------- //
	// --------------- 16B aligment --------------- //
	// -------------------------------------------- //
public:
	void* operator new(size_t i){ return _mm_malloc(i, 16); }
	void operator delete(void* p) { _mm_free(p); }
};
