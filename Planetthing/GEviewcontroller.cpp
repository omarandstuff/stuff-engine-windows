#include "GEviewcontroller.h"

// ------------------------------------------------------------------------------ //
// ------------------------------ View Load - Unload ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEViewController::viewDidLoad()
{
	texture = GETexture::textureWithFileName(L"resources/images/Test.png");
	fullscreen = GEFullScreen::sharedInstance();
}

// ------------------------------------------------------------------------------ //
// -------------------------- Update - Render - Layout -------------------------- //
// ------------------------------------------------------------------------------ //

void GEViewController::update()
{

}

void GEViewController::render()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	SwapBuffers(MainWindow->DeviceContext());
}

void GEViewController::didLayout(int width, int height)
{
	glViewport(0, 0, width, height);
	render();
}
