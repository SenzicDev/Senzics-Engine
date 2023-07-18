#include "WinDefine.h"
#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Main Window Class";
	wc.hIconSm = 0;
	Window myWindow(wc);

	// Message Loop
	MSG uMsg;
	BOOL exitCode = 0;
	while (exitCode = GetMessageW(&uMsg, 0, 0, 0))
	{
		TranslateMessage(&uMsg);
		DispatchMessageW(&uMsg);
	}

	if (exitCode == -1)
	{
		return -1;
	}

	return uMsg.wParam;
}