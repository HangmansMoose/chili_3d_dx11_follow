#include "ChiliWin.h"
#include <string>



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage( 69 );
		break;
		//WM_CHAR is a message about text input .. duh
		//Though, what might not be as obvious is that it also has a notion
		//of whether something is a capital letter (ie shift key pressed)
	case WM_CHAR:
		static std::string title;
		title.push_back( (char)wParam );
		SetWindowTextA(hWnd, title.c_str() );
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	const auto pClassName = LPCSTR("hw3dbutts");
	// register window class (all these are found in MSDN if need be)
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;

	//Note that I had an issue here because I was calling DefWindowProc instead of 
	//DefWindowProcA so my window title was displaying in Chinese. 
	//This is because it defaults to W if (A and W are the options to define what 
	//character set it being used where A is ANSI and W is UNICODE)

	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassExA(&wc);
	// create window instance
	HWND hWnd = CreateWindowExA(
		0, pClassName,
		LPCSTR("Happy Hard Window"),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);
	// show the damn window
	ShowWindow(hWnd, SW_SHOW);
	
	//windows is all about the messages .. and windows
	MSG msg;
	BOOL gResult;

	//Keep polling for a message, and if we receive one then translate it 
	while ((gResult = GetMessageA(&msg, nullptr, 0, 0)) > 0)
	{
		//Message must be translated for in order for Dispatch to be able to understand it.

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}