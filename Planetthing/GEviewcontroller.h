#pragma once
#include "GEwindow.h"
#include "GEopengl.h"

class GEViewController : public GEWindowProtocol
{
public:
	void update();
	void render();

	void didResized(int width, int height);
	void didRepaint();

public:
	GEWindow* MainWindow;
};
