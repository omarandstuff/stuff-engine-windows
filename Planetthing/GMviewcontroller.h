#pragma once
#include "GEwindow.h"
#include "GEupdatecaller.h"
#include "GMmain.h"

class GMViewController : public GEWindowProtocol
{
	// -------------------------------------------- //
	// --------- Update - Render - Layout --------- //
	// -------------------------------------------- //
public:
	void viewDidLoad();
	void update();
	void render();
	void didLayout(int width, int height);

	// -------------------------------------------- //
	// ------------------ Events ------------------ //
	// -------------------------------------------- //
private:

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GEWindow* MainWindow;

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
private:
	GEUpdateCaller* m_updateCaller;
};
