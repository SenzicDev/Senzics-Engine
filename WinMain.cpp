#include "WinDefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
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
	const LPCWSTR CLASS_NAME = L"Main Window Class";
	
	// Register Windows Class
	WNDCLASSEXW wc = {};
	wc.cbSize			= sizeof(WNDCLASSEXW);
	wc.style			= CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= 0;
	wc.hCursor			= 0;
	wc.hbrBackground	= 0;
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= CLASS_NAME;
	wc.hIconSm			= 0;
	RegisterClassExW(&wc);

	// Create Window
	HWND hWnd = CreateWindowExW(
		0,
		CLASS_NAME, L"Senzic's Engine", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		0, 0, hInstance, 0
	);

	ShowWindow(hWnd, SW_SHOW);

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