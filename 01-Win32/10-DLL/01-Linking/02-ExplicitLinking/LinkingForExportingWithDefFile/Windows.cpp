/*
Command to run this code -> Open Visual studio Developer Command Prompt and go to Windows.cpp file location and type following command - 
1. cl.exe /c /EHsc Windows.cpp
2. link.exe Windows.obj user32.lib gdi32.lib
*/

#include <windows.h>
//#include "MyMath.h"

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
	//Local Variable
	HMODULE hLib = NULL;
	typedef int (*PMAKECUBEFUNCTION)(int);
	PMAKECUBEFUNCTION pMakeCube = NULL;
	int num1, num2;
	TCHAR str[255];

	//Code
	switch (iMsg) {
	case WM_CREATE:
		hLib = LoadLibrary(TEXT("MyMath.dll"));
		if (hLib == NULL) {
			MessageBox(hwnd, TEXT("LoadLibrary Failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pMakeCube = (PMAKECUBEFUNCTION) GetProcAddress(hLib, "MakeCube");
		if (pMakeCube == NULL) {
			MessageBox(hwnd, TEXT("Make Cube function cannot obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		num1 = 15;
		num2 = pMakeCube(num1);
		wsprintf(str, TEXT("Cube of %d is %d"), num1, num2);
		MessageBox(hwnd, str, TEXT("CUBE FUNCTION"), MB_OK);
		FreeLibrary(hLib);
		DestroyWindow(hwnd); //Closing application
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
