#include "GEviewcontroller.h"

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

void GEViewController::didResized(int width, int height)
{
	glViewport(0, 0, width, height);
	render();
}

void GEViewController::didRepaint()
{
	
}
