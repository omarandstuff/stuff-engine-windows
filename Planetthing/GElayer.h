#pragma once

#include "GErenderable.h"

class GELayer : public GERenderable
{
public:
	GELayer();
	~GELayer();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	bool Visible;
	wstring Name;
	unsigned int NumberOfObjects;

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render(GE_RENDER_MODE mode);

	// -------------------------------------------- //
	// ----------- Add - Remove objects ----------- //
	// -------------------------------------------- //
public:
	void addObject(GERenderable* object);
	void removeObject(GERenderable* object);


	// -------------------------------------------- //
	// ------------- Private Members -------------- //
	// -------------------------------------------- //
private:
	vector<GERenderable*> m_objects;
};
