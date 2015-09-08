#pragma once

// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif
#include <atlimage.h>
#include "resource.h"
#include <string>
#include <vector>
using std::vector;
using std::wstring;
using std::to_wstring;

class GEWindowProtocol
{
public:
	virtual void didLayout(int width, int height) = 0;
};

class GEWindow
{
public:
	GEWindow();
	~GEWindow();

	VOID Init(BOOL centered = FALSE, BOOL minbutton = TRUE, BOOL maxbutton = TRUE, BOOL resizable = TRUE);
	VOID Create();

	// Window //
	VOID Maximize();
	VOID Minimize();
	VOID RestoreUp();
	VOID RestoreDown();
	VOID Show();
	VOID Hide();

	HWND hWnd();
	HDC DeviceContext();

	VOID WindowSize(UINT width, UINT height);
	VOID ClientSize(UINT width, UINT height);
	VOID Position(UINT top, UINT left);
	VOID WindowLeft(UINT value);
	VOID WindowTop(UINT value);
	VOID WindowWidth(UINT value);
	VOID WindowHeight(UINT value);
	UINT WindowLeft();
	UINT WindowTop();
	UINT WindowWidth();
	UINT WindowHeight();
	VOID ClientWidth(UINT value);
	VOID ClientHeight(UINT value);
	UINT ClientWidth();
	UINT ClientHeight();
	UINT ScreenWidth();
	UINT ScreenHeight();

	VOID Title(wstring value);
	wstring Title();

	VOID Enable();
	VOID Disable();

	VOID Opasity(BYTE alpha);
	BYTE Opasity();

	VOID SetLayeredWnd(DWORD resourceID);

	VOID FullScreen(BOOL value);

	VOID TopMost(BOOL value);

	VOID LayeredMovible(BOOL value);

	// -------------------------------------------- //
	// ------------ Delegate Management ----------- //
	// -------------------------------------------- //
	void addDelegate(GEWindowProtocol* delegate);
	void removeDelegate(void* delegate);

private:
	VOID RegClass();
	VOID Release();

	VOID MoveWnd();
	VOID AdjustWnd();
	VOID SetWindowMetrics();

	VOID SetLayeredWndAttributes();

	VOID MakeLayeredWnd();
private:
	static LRESULT CALLBACK GEWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	BOOL m_created;

	HDC	m_deviceContext = NULL;
	HWND m_hwnd;
	HWND m_parent;
	HMENU m_hMenu;
	wstring m_className;
	
	wstring m_windowTitle;

	DWORD m_style;

	BOOL m_minButton;
	BOOL m_maxButton;
	BOOL m_resizable;

	BOOL m_maximized;
	BOOL m_minimized;

	BOOL m_centered;

	UINT m_windowsTop;
	UINT m_windowLeft;
	UINT m_windowWidth;
	UINT m_windowHeight;

	UINT m_screenWidth;
	UINT m_screenHeight;

	// Initial client size
	BOOL m_initialClientSize;

	UINT m_clientWidth;
	UINT m_clientHeight;

	UINT m_deltaWidth;
	UINT m_deltaHeight;

	BYTE m_opasity;

	// Layered
	BOOL m_initialLeyeredWindow;
	BOOL m_isLayered;
	BOOL m_layeredMovible;
	HBITMAP m_layeredBitMap;
	BYTE* m_layeredPixels;
	UINT m_layeredBitMapWidth;
	UINT m_layeredBitMapHeight;

	// Full Screen
	BOOL m_fullScreen;

	BOOL m_savedExStyle;
	BOOL m_savedStyle;
	UINT m_savedTop;
	UINT m_savedLeft;
	UINT m_savedWidth;
	UINT m_savedHeight;

	// Events
	bool m_resized;
	vector<GEWindowProtocol*> m_delegates;

	static UINT count;
};
