#include <Windows.h>

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
	wc.lpfnWndProc = DefWindowProcA;
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

	//Keep polling for a message, and if we receive one then translate it 
	while (GetMessageA(&msg, nullptr, 0, 0) > 0)
	{
		//Message must be translated for in order for Dispatch to be able to understand it.

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	while (true);
	return 0;
}