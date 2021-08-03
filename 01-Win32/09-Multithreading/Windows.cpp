/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command - 
1. cl.exe /c /EHsc Windows.cpp
2. link.exe Windows.obj user32.lib gdi32.lib kernel32.lib
*/

#include <windows.h>
#include <tchar.h>
//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
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
	static HANDLE hThread1 = NULL;
	static HANDLE hThread2 = NULL;
	switch (iMsg) {
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		//Here should be error checking for hThread1
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		//Here should be error checking for hThread2
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("I am thread 4"), TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {
	//Variable Declaration
	HDC hdc = NULL;
	TCHAR str[255];
	long i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 0; i < 2147483647; i++) {
		wsprintf(str, TEXT("Incrementing Order = %ld"), i);
		TextOut(hdc, 5, 5, str, (int)_tcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {
	//Variable Declaration
	HDC hdc = NULL;
	TCHAR str[255];
	long i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));
	for (i = 2147483647; i >= 0; i--) {
		wsprintf(str, TEXT("Decrementing Order = %ld"), i);
		TextOut(hdc, 5, 25, str, (int)_tcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

