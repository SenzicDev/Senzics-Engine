#pragma once
#include "WinDefine.h"

// Each new Window instance will register a new win32 class
// Do not create a new Window object if you want to make a child window
class Window
{
private:
	Window();

	HINSTANCE hInst;
	LPCWSTR className;
	HWND hWnd;
	static LRESULT CALLBACK InstallCustomWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcProxy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT (CALLBACK *wndProcPtr)(HWND, UINT, WPARAM, LPARAM);

	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Window(WNDCLASSEXW wc);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

};
