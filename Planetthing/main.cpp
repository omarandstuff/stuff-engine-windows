#include "GEopengl.h"
#include "GEwindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, PSTR pScmdline, int iCmdShow)
{
	GEWindow main_window;

	main_window.Create();
	
	// Initialize OpenGL for render in the main window.
	glInit(main_window.DeviceContext());

	// Show the main window.
	main_window.Show();

	//////// Main Loop ///////
	MSG msg;
	bool done = false;

	// Loop until there is a quit message from the window or the user.
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
			done = true;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFlush();
			SwapBuffers(main_window.DeviceContext());
		}
	}

	// Finish all the stuff.
	return 1;
}
