/*
To see TLB File in OLE viwer : oleview.exe 

cl.exe /c /EHsc COMClient.cpp
link.exe COMClient.obj user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
*/

#include <windows.h>
#import "DotNetServer.tlb" no_namespace named_guids raw_interfaces_only
//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Variable Declaration 
IDispatch* pIDispatch = NULL;


//Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyFirstWindow");
	HRESULT hr;

	//Code
	//COM initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("COM Library can not be initialized. \nProgram will now exit."), TEXT("COM Initialization Error"), MB_OK);
		exit(0);
	}

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

	//COM Uninitialize 
	CoUninitialize();

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HRESULT hr;
	int iNum1, iNum2, iSum, iSub;
	TCHAR str[255];

	DISPID dispid;
	OLECHAR* szFunctionOne = L"SumOfTwoIntegers";
	OLECHAR* szFunctionTwo = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS params;


	//Code
	switch (iMsg) {
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_DotNetServer, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IDispatch interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 155;
		iNum2 = 145;

		VariantInit(vArg);

		//vt = Variant Type
		vArg[0].vt = VT_INT;
		vArg[0].intVal = iNum2;

		vArg[1].vt = VT_INT;
		vArg[1].intVal = iNum1;

		params.rgvarg = vArg;
		params.cArgs = 2;
		params.cNamedArgs = 0;
		params.rgdispidNamedArgs = NULL;

		VariantInit(&vRet);

		//Sum
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionOne, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("GetId name failed"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vRet, NULL, NULL);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Sum : Invoke failed"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Sum of two integers"), MB_OK);

		//Subtraction
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionTwo, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Subtraction : GetId name failed"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vRet, NULL, NULL);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Subtraction : Invoke failed"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("Subtraction of two integers"), MB_OK);

		if (pIDispatch) {
			pIDispatch->Release();
			pIDispatch = NULL;
		}

		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
