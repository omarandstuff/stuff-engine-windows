#include "GMviewcontroller.h"

// ------------------------------------------------------------------------------ //
// ------------------------------ View Load - Unload ---------------------------- //
// ------------------------------------------------------------------------------ //

void GMViewController::viewDidLoad()
{
	m_updateCaller = GEUpdateCaller::sharedInstance();
	GMMain::sharedInstance();
}

// ------------------------------------------------------------------------------ //
// -------------------------- Update - Render - Layout -------------------------- //
// ------------------------------------------------------------------------------ //

void GMViewController::update()
{
	// Pre update scene.
	m_updateCaller->preUpdate();

	// Update scene.
	m_updateCaller->update();
}

void GMViewController::render()
{
	// Render scene.
	m_updateCaller->render();

	// glFlush for i don't remeber what.
	glFlush();

	// Present final image.
	SwapBuffers(MainWindow->DeviceContext());

	// Post update scene.
	m_updateCaller->posUpdate();
}

void GMViewController::didLayout(int width, int height)
{
	// Layout everything
	m_updateCaller->layout(width, height);

	// Render Again for the new size.
	render();
}
