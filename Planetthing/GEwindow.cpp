#include "GEwindow.h"

unsigned int GEWindow::count = 0;

GEWindow::GEWindow(HWND parent, bool centered, bool minbutton, bool maxbutton, bool resizable)
{
	m_windowTitle = L"Window" + to_wstring(count + 1);

	create(parent, centered, minbutton, maxbutton, resizable);
}

GEWindow::~GEWindow()
{

}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Creation --------------------------------- //
// ------------------------------------------------------------------------------ //

void GEWindow::create(HWND parent, bool centered, bool minbutton, bool maxbutton, bool resizable)
{
	WNDCLASSEX wc = { 0 };

	// Windows regidtration parameters.
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(APPICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(APPICON), IMAGE_ICON, 16, 16, 0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = GEWindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = m_windowTitle.data();
	wc.hbrBackground = NULL;

	RegisterClassEx(&wc);

	// Basic style.
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

	// Style
	if (resizable) style |= WS_THICKFRAME;
	if (maxbutton) style |= WS_MAXIMIZEBOX;
	if (minbutton) style |= WS_MINIMIZEBOX;
	if (parent) style |= WS_CHILD;

	// Create the window object.
	m_hwnd = CreateWindowEx(WS_EX_LAYERED, m_windowTitle.data(), m_windowTitle.data(), style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, parent, NULL, GetModuleHandle(NULL), this);

	// Device context
	m_deviceContext = GetDC(m_hwnd);

	// Entended windows seems to requare this.
	SetLayeredWindowAttributes(m_hwnd, NULL, 255, LWA_ALPHA);

	// Plus window at the static value.
	count++;
}

// ------------------------------------------------------------------------------ //
// ------------------------------- Message Handling ----------------------------- //
// ------------------------------------------------------------------------------ //

LRESULT CALLBACK GEWindow::GEWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GEWindow *pThis = NULL;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (GEWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		pThis->hWnd(hwnd);
	}
	else
	{
		pThis = (GEWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}
	if (pThis)
	{
		return pThis->HandleMessage(hwnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT GEWindow::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool resized = false;
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		count--;
		if (count == 0) PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		if (resized && !(m_clientWidth == 0 && m_clientHeight == 0))
		{
			for (vector<GEWindowProtocol*>::iterator it = m_delegates.begin(); it != m_delegates.end(); it++)
			{
				(*it)->didLayout(m_clientWidth, m_clientHeight);
			}
			resized = false;
		}
		return 0;
	}
	case WM_SIZE:
	{
		resized = true;
		getClientSize();
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		for (vector<GEWindowInputProtocol*>::iterator it = m_inputDelegates.begin(); it != m_inputDelegates.end(); it++)
			(*it)->mouseMove((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));

		return 0;
	}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void GEWindow::getClientSize()
{
	RECT rect;

	// Get the size of the client area.
	GetClientRect(m_hwnd, &rect);

	m_clientWidth = rect.right - rect.left;
	m_clientHeight = rect.bottom - rect.top;
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Behaivour -------------------------------- //
// ------------------------------------------------------------------------------ //

void GEWindow::show()
{
	ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

// ------------------------------------------------------------------------------ //
// ------------------------------ Delegate management --------------------------- //
// ------------------------------------------------------------------------------ //
void GEWindow::addDelegate(GEWindowProtocol* delegate)
{
	m_delegates.push_back(delegate);
}

void GEWindow::addInputDelegate(GEWindowInputProtocol* delegate)
{
	m_inputDelegates.push_back(delegate);
}

void GEWindow::removeDelegate(void* delegate)
{
	// If selector is in window delegates.
	for (vector<GEWindowProtocol*>::iterator it = m_delegates.begin(); it != m_delegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_delegates.erase(it);
			return;
		}
	}

	// If selector is in input delgates.
	for (vector<GEWindowInputProtocol*>::iterator it = m_inputDelegates.begin(); it != m_inputDelegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_inputDelegates.erase(it);
			return;
		}
	}
}

// ------------------------------------------------------------------------------ //
// ------------------------------- Getters / Setters ---------------------------- //
// ------------------------------------------------------------------------------ //

HWND GEWindow::hWnd()
{
	return m_hwnd;
}

void GEWindow::hWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}

HDC GEWindow::deviceContext()
{
	return  m_deviceContext;
}
