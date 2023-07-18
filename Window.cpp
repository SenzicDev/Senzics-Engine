#include "Window.h"

// Registers a new window class then creates and shows the main window
Window::Window(WNDCLASSEXW wc)
{
	this->hInst = wc.hInstance;
	this->className = wc.lpszClassName;
	this->wndProcPtr = reinterpret_cast<LRESULT (*)(HWND, UINT, WPARAM, LPARAM)>(wc.lpfnWndProc);

	// Register Class
	wc.lpfnWndProc = InstallCustomWndProc;
	RegisterClassExW(&wc);

	// Create Main Window
	hWnd = CreateWindowExW(
		0,
		className,
		L"Senzic's Engine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		0, 0, hInst, this
	);

	ShowWindow(hWnd, SW_SHOW);
}

// Unregisters the window class
// !!!Make sure this runs before DefWinProc handles WM_QUIT!!!
Window::~Window()
{
	UnregisterClassW(className, hInst);
}

LRESULT Window::InstallCustomWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WndProcProxy));
		return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::WndProcProxy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongW(hWnd, GWLP_USERDATA));
	return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (wndProcPtr != nullptr)
	{
		return wndProcPtr(hWnd, uMsg, wParam, lParam);
	}

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(LoadCursorW(0, IDC_ARROW));
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}