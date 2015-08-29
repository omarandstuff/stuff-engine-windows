#include "GElayer.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GELayer::GELayer()
{
	Visible = true;
}

GELayer::~GELayer()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GELayer::render(GE_RENDER_MODE mode)
{
	// Render every object of this layer.
	for (vector<GERenderable*>::iterator object = m_objects.begin(); object != m_objects.end(); object++)
		(*object)->render(mode);
}

// ------------------------------------------------------------------------------ //
// ---------------------------- Add - Remove objects ---------------------------- //
// ------------------------------------------------------------------------------ //

void GELayer::addObject(GERenderable* object)
{
	m_objects.push_back(object);
	NumberOfObjects++;
}

void GELayer::removeObject(GERenderable* object)
{
	for (vector<GERenderable*>::iterator _object = m_objects.begin(); _object != m_objects.end(); _object++)
	{
		if (*_object._Ptr == object)
		{
			m_objects.erase(_object);
			NumberOfObjects--;
			return;
		}
	}
}
