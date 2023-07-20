#pragma once
#include "WinDefine.h"

namespace SZE
{
	// Each new Window instance will register a new win32 class
	// Do not create a new Window object if you want to make a child window
	class Window
	{
		// Mouse and Keyboard Interfaces
	private:
		class Keyboard
		{

		};

		class Mouse
		{

		};

		// Public Interface
	public:
		Window();
		Window(LRESULT CALLBACK WndCallProc(HWND, UINT, WPARAM, LPARAM));
		Window(const WNDCLASSEXW& wc);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Keyboard	keyboard;
		Mouse		mouse;

		void NewWindow(int posX = 0, int posY = 0, int width = 960, int height = 540, DWORD styles = WS_OVERLAPPEDWINDOW);

		bool ProcessMessages();

		// Private Members
	private:
		static unsigned int registeredClassCount;

		HWND		hWnd;
		HINSTANCE	hInst;
		LPCWSTR		className;

		static LRESULT CALLBACK WndProcProxy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}