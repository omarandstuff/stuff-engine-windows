#include "GEwindow.h"

unsigned int GEWindow::count = 0;

GEWindow::GEWindow()
{
	m_windowTitle = L"Window" + to_wstring(count + 1);
	m_className = L"Window" + to_wstring(count + 1);
	m_created = FALSE;
	m_parent = NULL;
	m_minButton = TRUE;
	m_maxButton = TRUE;
	m_resizable = TRUE;
	m_centered = FALSE;
	m_windowsTop = CW_USEDEFAULT;
	m_windowLeft = CW_USEDEFAULT;
	m_windowWidth = CW_USEDEFAULT;
	m_windowHeight = CW_USEDEFAULT;
	m_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_initialClientSize = FALSE;
	m_opasity = 255;
	m_initialLeyeredWindow = FALSE;
	m_isLayered = FALSE;
	m_layeredMovible = TRUE;
	m_layeredBitMap = NULL;
	m_resized = FALSE;

	m_maximized = FALSE;
	m_minimized = FALSE;
}

GEWindow::~GEWindow()
{
	Release();
}

VOID GEWindow::Release()
{
	if (m_created)
	{
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;

		// Remove the application instance.
		UnregisterClass(m_className.data(), GetModuleHandle(NULL));
	}
}

VOID GEWindow::Init(BOOL centered, BOOL minbutton, BOOL maxbutton, BOOL resizable)
{
	m_centered = centered;
	m_minButton = minbutton;
	m_maxButton = maxbutton;
	m_resizable = resizable;
}

VOID GEWindow::Create()
{
	RegClass();

	m_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

	if(m_resizable)
		m_style |= WS_THICKFRAME;

	if(m_maxButton)
		m_style |= WS_MAXIMIZEBOX;

	if(m_minButton)
		m_style |= WS_MINIMIZEBOX;

	if(m_parent)
	{
		m_style |= WS_CHILD;
	}

	if(m_initialLeyeredWindow) m_style = WS_POPUP;

	m_hwnd = CreateWindowEx(WS_EX_LAYERED, m_className.data(), m_windowTitle.data(), m_style, m_windowLeft, m_windowsTop, m_windowWidth, m_windowHeight, m_parent, m_hMenu, GetModuleHandle(NULL), this);

	// Created flag.
	m_created = TRUE;

	// if we have an initial client size we do the next i dont want to explain.
	if(m_initialClientSize)
	{
		UINT w = m_clientWidth;
		UINT h = m_clientHeight;

		SetWindowMetrics();

		ClientSize(w, h);
	}
	else
	{
		// Get the size and position gain at creating.
		SetWindowMetrics();
	}

	if(m_initialLeyeredWindow)
	{
		MakeLayeredWnd();
	}
	else
	{
		// Initial opasity.
		SetLayeredWndAttributes();
	}

	// If centered, center the god damn window.
	if (m_centered)
	{
		m_windowLeft = (GetSystemMetrics(SM_CXSCREEN) - m_windowWidth) / 2;
		m_windowsTop = (GetSystemMetrics(SM_CYSCREEN) - m_windowHeight) / 2;
	}

	MoveWnd();

	// Plus window at the static value.
	count++;
}

VOID GEWindow::RegClass()
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(APPICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(APPICON), IMAGE_ICON, 16, 16, 0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = GEWindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = m_className.data();

	RegisterClassEx(&wc);
}

LRESULT CALLBACK GEWindow::GEWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GEWindow *pThis = NULL;

	if(uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (GEWindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->m_hwnd = hwnd;
	}
	else
	{
		pThis = (GEWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}
	if(pThis)
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
	switch(uMsg)
	{
	case WM_DESTROY:
	{
		count--;
		if (count == 0) PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
		return 0;
	}
	case WM_SIZE:
	{
		SetWindowMetrics();
		m_resized = TRUE;
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		m_mouseMove = true;
		return 0;
	}
	case WM_NCHITTEST:
	{
		if (m_isLayered && m_layeredMovible)
			return HTCAPTION;
	}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

HWND GEWindow::hWnd()
{
	return m_hwnd;
}

VOID GEWindow::SetWindowMetrics()
{
	RECT rect;
	GetWindowRect(m_hwnd, &rect);

	m_windowWidth = rect.right - rect.left;
	m_windowHeight = rect.bottom - rect.top;
	m_windowLeft = rect.left;
	m_windowsTop = rect.top;

	// Get the size of the client area.
	GetClientRect(m_hwnd, &rect);

	m_clientWidth = rect.right - rect.left;
	m_clientHeight = rect.bottom - rect.top;

	// Size diference from metrics
	m_deltaWidth = m_windowWidth - m_clientWidth;
	m_deltaHeight = m_windowHeight - m_clientHeight;
}

VOID GEWindow::Maximize()
{
	if(m_isLayered || m_fullScreen) return;
	m_maximized = TRUE;
	Show();
}

VOID GEWindow::Minimize()
{
	m_minimized = TRUE;
	Show();
}

VOID GEWindow::RestoreUp()
{
	if(m_minimized)
	{
		m_minimized = FALSE;
		Show();
	}
}

VOID GEWindow::RestoreDown()
{
	if(m_isLayered || m_fullScreen) return;
	if(m_maximized)
	{
		m_maximized = FALSE;
		Show();
	}
}

VOID GEWindow::Show()
{
	if (!m_created)
	{
		Create();
	}
	if(m_maximized && m_minimized)
	{
		ShowWindow(m_hwnd, SW_MAXIMIZE);
		ShowWindow(m_hwnd, SW_MINIMIZE);
	}
	else if(m_maximized)
	{
		ShowWindow(m_hwnd, SW_MAXIMIZE);
	}
	else if(m_minimized)
	{
		ShowWindow(m_hwnd, SW_MINIMIZE);
	}
	else
	{
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
	}
	UpdateWindow(m_hwnd);
}

VOID GEWindow::Hide()
{
	if(!m_created) return;
	ShowWindow(m_hwnd, SW_HIDE);
}

VOID GEWindow::MoveWnd()
{
	if(!m_created) return;
	MoveWindow(m_hwnd, m_windowLeft, m_windowsTop, m_windowWidth, m_windowHeight, TRUE);
}

VOID GEWindow::WindowSize(UINT width, UINT height)
{
	if(m_isLayered || m_fullScreen) return;
	m_windowWidth = width;
	m_windowHeight = height;
	MoveWnd();
}

VOID GEWindow::Position(UINT top, UINT left)
{
	if(m_fullScreen) return;
	m_windowsTop = top;
	m_windowLeft = left;
	MoveWnd();
}

VOID GEWindow::WindowLeft(UINT value)
{
	if(m_fullScreen) return;
	m_windowLeft = value;
	MoveWnd();
}

VOID GEWindow::WindowTop(UINT value)
{
	if(m_fullScreen) return;
	m_windowsTop = value;
	MoveWnd();
}

VOID GEWindow::WindowWidth(UINT value)
{
	if(m_isLayered || m_fullScreen) return;
	m_windowWidth = value;
	MoveWnd();
}

VOID GEWindow::WindowHeight(UINT value)
{
	if(m_isLayered || m_fullScreen) return;
	m_windowHeight = value;
	MoveWnd();
}

UINT GEWindow::WindowLeft()
{
	return m_windowLeft;
}

UINT GEWindow::WindowTop()
{
	return m_windowsTop;
}

UINT GEWindow::WindowWidth()
{
	return m_windowWidth;
}

UINT GEWindow::WindowHeight()
{
	return m_windowHeight;
}

VOID GEWindow::ClientSize(UINT width, UINT height)
{
	if(m_isLayered || m_fullScreen) return;
	m_clientWidth = width;
	m_clientHeight = height;
	AdjustWnd();
}

VOID GEWindow::ClientWidth(UINT value)
{
	if(m_isLayered || m_fullScreen) return;
	m_clientWidth = value;
	AdjustWnd();
}

VOID GEWindow::ClientHeight(UINT value)
{
	if(m_isLayered || m_fullScreen) return;
	m_clientHeight = value;
	AdjustWnd();
}

UINT GEWindow::ClientWidth()
{
	return m_clientWidth;
}

UINT GEWindow::ClientHeight()
{
	return m_clientHeight;
}

VOID GEWindow::AdjustWnd()
{
	if(!m_created)
	{
		m_initialClientSize = TRUE;
		return;
	}
	m_windowWidth = m_clientWidth + m_deltaWidth;
	m_windowHeight = m_clientHeight + m_deltaHeight;
	MoveWnd();
}

VOID GEWindow::Title(wstring value)
{
	m_windowTitle = value;
	if(m_created) SetWindowText(m_hwnd, m_windowTitle.data());
}

wstring GEWindow::Title()
{
	return m_windowTitle;
}

VOID GEWindow::Enable()
{
	EnableWindow(m_hwnd, true);
}

VOID GEWindow::Disable()
{
	EnableWindow(m_hwnd, false);
}

VOID GEWindow::SetLayeredWndAttributes()
{
	if(!m_created) return;
	SetLayeredWindowAttributes(m_hwnd, NULL, m_opasity, LWA_ALPHA);
}

VOID GEWindow::Opasity(BYTE alpha)
{
	m_opasity = alpha;
	if(m_isLayered)
	{

	}
	else
		SetLayeredWndAttributes();
}

BYTE GEWindow::Opasity()
{
	return m_opasity;
}

VOID GEWindow::SetLayeredWnd(DWORD resourceID)
{
	CImage cPngImage;
	HMODULE hModule = GetModuleHandle(NULL);

	HRSRC src = FindResource(hModule, MAKEINTRESOURCE(resourceID), _T("PNG"));

	HGLOBAL hGlobal = LoadResource(hModule, src);

	PVOID pResourceData = LockResource(hGlobal);

	INT nSize = SizeofResource(hModule, src);

	IStream *pStream = NULL;
	DWORD  dwReadWrite = 0;

	CreateStreamOnHGlobal(NULL, TRUE, &pStream);

	pStream->Write(pResourceData, nSize, &dwReadWrite);

	cPngImage.Load(pStream);

	HBITMAP bitmap = cPngImage.Detach();

	pStream->Release();

	BITMAP bm;
	GetObject(bitmap, sizeof(bm), &bm);

	m_layeredBitMapWidth = bm.bmWidth;
	m_layeredBitMapHeight = bm.bmHeight;

	HDC dcBitmap = CreateCompatibleDC(NULL);
	SelectObject(dcBitmap, bitmap);

	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = bm.bmWidth;
	bmpInfo.bmiHeader.biHeight = -bm.bmHeight;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;

	BYTE* pixel = new BYTE[bm.bmWidth * bm.bmHeight * 4];
	GetDIBits(dcBitmap, bitmap, 0, bm.bmHeight, pixel, &bmpInfo, DIB_RGB_COLORS);

	if(m_layeredPixels) delete[] m_layeredPixels;
	m_layeredBitMap = CreateDIBSection(dcBitmap, &bmpInfo, DIB_RGB_COLORS, (void**)&m_layeredPixels, NULL, 0);

	for(int i = 0; i < m_layeredBitMapWidth * m_layeredBitMapHeight; i++)
	{
		m_layeredPixels[i * 4] = pixel[i * 4] * pixel[i * 4 + 3] / 255;
		m_layeredPixels[i * 4 + 1] = pixel[i * 4 + 1] * pixel[i * 4 + 3] / 255;
		m_layeredPixels[i * 4 + 2] = pixel[i * 4 + 2] * pixel[i * 4 + 3] / 255;
		m_layeredPixels[i * 4 + 3] = pixel[i * 4 + 3];
	}

	delete[] pixel;

	m_isLayered = TRUE;

	m_windowWidth = m_clientWidth = m_layeredBitMapWidth;
	m_windowHeight = m_clientHeight = m_layeredBitMapHeight;

	m_maximized = FALSE;

	m_centered = true;


	if(!m_created)
		m_initialLeyeredWindow = TRUE;
	else
		MakeLayeredWnd();
}

VOID GEWindow::MakeLayeredWnd()
{
	HGDIOBJ hPrevObj = NULL;
	POINT ptDest = { 0, 0 };
	POINT ptSrc = { 0, 0 };
	SIZE client = { m_layeredBitMapWidth, m_layeredBitMapHeight };

	// create a memory DC holding the splash bitmap
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmpOld = (HBITMAP)SelectObject(hdcMem, m_layeredBitMap);

	// use the source image's alpha channel for blending
	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	// paint the window (in the right location) with the alpha-blended bitmap
	UpdateLayeredWindow(m_hwnd, hdcScreen, &ptDest, &client, hdcMem, &ptSrc, RGB(0, 0, 0), &blend, ULW_ALPHA);

	// delete temporary objects
	SelectObject(hdcMem, hbmpOld);
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdcScreen);

}

VOID GEWindow::FullScreen(BOOL value)
{
	if(m_isLayered) return;
	m_fullScreen = value;
	
	if(m_fullScreen)
	{
		Hide();
		m_savedExStyle = GetWindowLong(m_hwnd, GWL_EXSTYLE);
		m_savedStyle = GetWindowLong(m_hwnd, GWL_STYLE);
		
		SetWindowMetrics();

		m_savedTop = m_windowsTop;
		m_savedLeft = m_windowLeft;
		m_savedWidth = m_windowWidth;
		m_savedHeight = m_windowHeight;

		SetWindowLong(m_hwnd, GWL_EXSTYLE, 0);
		SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		SetWindowPos(m_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		m_windowWidth = GetSystemMetrics(SM_CXSCREEN);
		m_windowHeight = GetSystemMetrics(SM_CYSCREEN);
		m_windowsTop = 0;
		m_windowLeft = 0;

		SetWindowPos(m_hwnd, HWND_NOTOPMOST, m_windowLeft, m_windowsTop, m_windowWidth, m_windowHeight, SWP_SHOWWINDOW);

		SetWindowMetrics();

		Show();
	}
	else
	{
		SetWindowLong(m_hwnd, GWL_EXSTYLE, m_savedExStyle);
		SetWindowLong(m_hwnd, GWL_STYLE, m_savedStyle);
		SetWindowPos(m_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		m_windowsTop = m_savedTop;
		m_windowLeft = m_savedLeft;

		m_windowWidth = m_savedWidth;
		m_windowHeight = m_savedHeight;

		SetWindowPos(m_hwnd, HWND_NOTOPMOST, m_windowLeft, m_windowsTop, m_windowWidth, m_windowHeight, SWP_SHOWWINDOW);

		SetWindowMetrics();
	}
}

VOID GEWindow::TopMost(BOOL value)
{
	if(!m_created || m_fullScreen) return;

	HWND topmost = value? HWND_TOPMOST : HWND_NOTOPMOST;

	SetWindowPos(m_hwnd, topmost, m_windowLeft, m_windowsTop, m_windowWidth, m_windowHeight, SWP_SHOWWINDOW);
}

VOID GEWindow::LayeredMovible(BOOL value)
{
	m_layeredMovible = value;
}

UINT GEWindow::ScreenWidth()
{
	return m_screenWidth;
}

UINT GEWindow::ScreenHeight()
{
	return m_screenHeight;
}

BOOL GEWindow::Resized()
{
	if (m_resized)
	{
		m_resized = FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL GEWindow::MouseMove()
{
	if (m_mouseMove)
	{
		m_mouseMove = false;
		return true;
	}
	return false;
}
