#include "WinDefine.h"
#include "Window.h"

namespace SZE
{
	unsigned int Window::registeredClassCount = 0;

	Window::Window() : Window::Window(nullptr){}

	Window::Window(WNDPROC WndCallProc)
		: hInst(GetModuleHandleW(nullptr))
	{
		Window::registeredClassCount++;
		className = (LPCWSTR)("SZE Window Class " + Window::registeredClassCount);

		if (WndCallProc == nullptr)
			WndCallProc = WndProcProxy;

		WNDCLASSEXW wc = {};
		wc.cbSize			= sizeof(WNDCLASSEXW);
		wc.style			= 0;
		wc.lpfnWndProc		= WndCallProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= hInst;
		wc.hIcon			= 0;
		wc.hCursor			= 0;
		wc.hbrBackground	= 0;
		wc.lpszMenuName		= 0;
		wc.lpszClassName	= className;
		wc.hIconSm			= 0;
		RegisterClassExW(&wc);
	}

	Window::Window(const WNDCLASSEXW& wc)
		: hInst(GetModuleHandleW(nullptr))
	{
		Window::registeredClassCount++;
		const char* cn = "SZE Window Class " + Window::registeredClassCount;
		RegisterClassExW(&wc);
	}

	Window::~Window()
	{
		UnregisterClassW(className, hInst);
	}

	void Window::NewWindow(int posX = 0, int posY = 0, int width = 960, int height = 540, DWORD styles = WS_OVERLAPPEDWINDOW)
	{
		CreateWindowExW(
			0,
			className,
			L"Senzic's Engine",
			WS_OVERLAPPEDWINDOW,
			posX, posY, width, height,
			hWnd,
			0,
			hInst,
			this
		);

		SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG)this);

		ShowWindow(hWnd, SW_SHOWNORMAL);
	}

	bool Window::ProcessMessages()
	{
		MSG msg;
		while (PeekMessageW(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
			if (msg.message == WM_QUIT)
			{
				return false;
			}
		}
		return true;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_QUIT:
			return 0;

		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		case WM_SETCURSOR:
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(LoadCursorW(hInst, IDC_ARROW));
			}
			break;
		}

		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK Window::WndProcProxy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))->WndProc(hWnd, uMsg, wParam, lParam);
	}
}