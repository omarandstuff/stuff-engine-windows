#include "GMviewcontroller.h"

// ------------------------------------------------------------------------------ //
// ------------------------------ View Load - Unload ---------------------------- //
// ------------------------------------------------------------------------------ //

void GMViewController::viewDidLoad()
{
	// Get the update caller.
	m_updateCaller = GEUpdateCaller::sharedInstance();

	// Initialize the shared input object.
	GEInput::sharedInstance();

	// Initialize the Main game entry object.
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

	// Post update scene.
	m_updateCaller->posUpdate();
}

void GMViewController::render()
{
	// Render scene.
	m_updateCaller->render();

	// glFlush for i don't remeber what.
	glFlush();

	// Present final image.
	SwapBuffers(MainWindow->deviceContext());
}

void GMViewController::didLayout(int width, int height)
{
	// Layout everything
	m_updateCaller->layout(width, height);

	// Render Again for the new size.
	render();
}
