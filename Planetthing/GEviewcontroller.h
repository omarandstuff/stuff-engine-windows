#pragma once
#include "GEwindow.h"
#include "GEtexture.h"

class GEViewController : public GEWindowProtocol
{
public:
	// -------------------------------------------- //
	// --------- Update - Render - Layout --------- //
	// -------------------------------------------- //
	void viewDidLoad();
	void update();
	void render();
	void didLayout(int width, int height);

	// -------------------------------------------- //
	// ------------------ Events ------------------ //
	// -------------------------------------------- //


public:
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
	GEWindow* MainWindow;
};
