/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command - 
1. cl.exe /c /EHsc Windows.cpp
2. link.exe Windows.obj user32.lib gdi32.lib
*/

#include <windows.h>
#define ID_TIMER1 101
//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaration 

//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyFirstWindow");

	//Code
	
	//Step 1 - Initialize wndclass structure
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Step 2 - Register wndclass structure
	RegisterClassEx(&wndclass);

	//Step 3 - Create Window in Memory
	hwnd = CreateWindow(szAppName,
		TEXT("OAD : My First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Steps 4 - Show Window
	ShowWindow(hwnd, iCmdShow);

	//Steps 5 - To Color window
	UpdateWindow(hwnd);

	//Steps 6 - Heart of the body i.e Message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	//Code
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static int iPaintFlag = 0;
	switch (iMsg) {
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER1, 1000, NULL);
		break;
	case WM_TIMER:
		KillTimer(hwnd, ID_TIMER1);
		iPaintFlag++;
		if (iPaintFlag >= 8) {
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, ID_TIMER1, 1000, NULL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1) {
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
		}
		else if (iPaintFlag == 2) {
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (iPaintFlag == 3) {
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (iPaintFlag == 4) {
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iPaintFlag == 5) {
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iPaintFlag == 6) {
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iPaintFlag == 7) {
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
		}
		else if (iPaintFlag == 8) {
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
		}
		else /*if (iPaintFlag == 0)*/ {
			hbrush = CreateSolidBrush(RGB(150, 150, 150));
		}
		SelectObject(hdc, hbrush);
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default:
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
