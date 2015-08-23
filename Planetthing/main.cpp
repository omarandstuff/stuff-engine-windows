#include "GEviewcontroller.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, PSTR pScmdline, int iCmdShow)
{
	GEWindow main_window;
	GEViewController main_viewControler;

	// Share the main window with the view controller.
	main_viewControler.MainWindow = &main_window;

	// Create the main window.
	main_window.Create();
	
	// Initialize OpenGL for render in the main window.
	glInit(main_window.DeviceContext());

	// Show the main window.
	main_window.Show();

	// Add the view controller to the window as a delegate.
	main_window.addDelegate(&main_viewControler);

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
			main_viewControler.update();
			main_viewControler.render();
		}
	}

	// Finish all the stuff.
	return 1;
}
