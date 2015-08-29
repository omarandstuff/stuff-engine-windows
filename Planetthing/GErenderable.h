#pragma once

#include "GEcommon.h"

class GERenderable
{
public:
	virtual void render(enum GE_RENDER_MODE mode) = 0;
};
