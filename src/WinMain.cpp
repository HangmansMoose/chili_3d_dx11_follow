#include <sstream>
#include "WindowsMessageMap.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static WindowsMessageMap mm;
	OutputDebugStringA( mm(msg, lParam, wParam).c_str() );
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(  69 );
		break;
	case WM_KEYDOWN:
		if( wParam == 'F' )
		{
			SetWindowTextA(hWnd, "PEAN" );
		}
		break;

	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowTextA(hWnd, "Willies");
		}
		break;

	case WM_CHAR:
    {
      static std::string title;
      title.push_back ( (char)wParam );
      SetWindowTextA( hWnd, title.c_str() );
    }
		break;

  }
	

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance, 
					 LPSTR lpCmdLine,
					 int nCmdShow) 
{
  // Create Window Class
  LPCWSTR pClassName = L"hw3dbutts";
  WNDCLASSEXW wc = {0};
  wc.cbSize = sizeof(wc);
  wc.style = CS_OWNDC;
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

  // Register Class
  RegisterClassExW(&wc);

  // Create Window
  HWND hWnd = CreateWindowExW(
      0, pClassName, L"Happy Hard Window",
      WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 200, 200, // Window Position
      640, 480,                                           // Window Size
      nullptr, nullptr,    // Handle to parent, handle to menu
      hInstance, nullptr); // hInstance and lpParam (optional settings we can
                           // pass to the window)

  // Show Window
  ShowWindow(hWnd, SW_SHOW);

  // Message Pump
  MSG msg;
  BOOL gResult;
  while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if (gResult == -1) {
    // This means GetMessage call has failed entirely
    return -1;
  } else {
    return msg.wParam;
  }
  return 0;
}
