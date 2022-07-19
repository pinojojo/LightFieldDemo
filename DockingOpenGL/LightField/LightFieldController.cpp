
#include "LightFieldController.h"
#include <Windows.h>

#include <GLCore.h>
#include <GLCoreUtils.h>

LRESULT CALLBACK  AffinityWindowProc(HWND hWnd, UINT uMsg, WPARAM	wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 创建光场图像所在窗口
void LightFieldController::CreateAffinityWindow(int positionX, int positionY, int width, int height)
{
	std::cout << "Creating" << std::endl;
	// 注册窗口类
	WNDCLASS	wc;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)AffinityWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WC_AFFINITY";
	RegisterClass(&wc);

	GLuint		PixelFormat;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	dwExStyle = WS_EX_APPWINDOW;
	dwStyle = WS_POPUP;

	//dwStyle = WS_CAPTION;

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

	HWND hWnd;

	if (!(hWnd = CreateWindowEx(dwExStyle,
		L"WC_AFFINITY",
		L"AffinityWindow",
		dwStyle |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		positionX, positionY,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		MessageBox(NULL, L"FAILED TO CREATE THREAD WINDOW", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
	}

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC hDC;
	HGLRC hRC;

	if (!(hDC = GetDC(hWnd)))
	{

		MessageBox(NULL, L"NO DC", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{

		MessageBox(NULL, L"CAN'T MATCH RC DC", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{

		MessageBox(NULL, L"CAN'T SET PFD", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	}

	if (!(hRC = wglCreateContext(hDC)))
	{

		MessageBox(NULL, L"CAN'T CREATE GL RC", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	}

	if (!wglMakeCurrent(hDC, hRC))
	{

		MessageBox(NULL, L"CAN'T MAKE CURRENT RC TO DC", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

}

LightFieldController::LightFieldController()
{

}
