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
#include <Windowsx.h> 
#endif
#include <atlimage.h>
#include "resource.h"
#include <string>
#include <vector>
using std::vector;
using std::wstring;
using std::to_wstring;


// -------------------------------------------- //
// ----------------- Protocols ---------------- //
// -------------------------------------------- //

class GEWindowProtocol
{
public:
	virtual void didLayout(int width, int height) = 0;
};

class GEWindowInputProtocol
{
public:
	virtual void mouseMove(float coordX, float coordY) = 0;
	//virtual void mouseDown(int button, float coordX, float coordY) = 0;
	//virtual void mouseUp(int button, float coordX, float coordY) = 0;
};

class GEWindow
{
public:
	GEWindow(HWND parent = NULL, bool centered = false, bool minbutton = true, bool maxbutton = true, bool resizable = true);
	~GEWindow();

	// -------------------------------------------- //
	// ------------------ Behaviour --------------- //
	// -------------------------------------------- //
public:
	void show();

	// -------------------------------------------- //
	// ------------- Message handling ------------- //
	// -------------------------------------------- //
private:
	static LRESULT CALLBACK GEWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
private:
	wstring m_windowTitle;
	HWND m_hwnd;
	HDC	m_deviceContext;

	// -------------------------------------------- //
	// ------------- Getter / Setters ------------- //
	// -------------------------------------------- //
public:
	HWND hWnd();
	void hWnd(HWND hwnd);
	HDC deviceContext();

	// -------------------------------------------- //
	// ------------ Delegate Management ----------- //
	// -------------------------------------------- //
public:
	void addDelegate(GEWindowProtocol* delegate);
	void addInputDelegate(GEWindowInputProtocol* delegate);
	void removeDelegate(void* delegate);

	// -------------------------------------------- //
	// -------------- Private members ------------- //
	// -------------------------------------------- //
private:
	void create(HWND parent = NULL, bool centered = false, bool minbutton = true, bool maxbutton = true, bool resizable = true);
	void getClientSize();

private:
	static UINT count;

	// Metrics
	unsigned int m_clientWidth;
	unsigned int m_clientHeight;

	// Delegates
	vector<GEWindowProtocol*> m_delegates;
	vector<GEWindowInputProtocol*> m_inputDelegates;
};
