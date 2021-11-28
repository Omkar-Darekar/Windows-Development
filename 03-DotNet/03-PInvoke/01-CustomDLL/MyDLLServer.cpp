/*
* cl.exe /c /EHsc MyDLLServer.cpp
* link.exe MyDLLServer.obj /DLL /DEF:MyDLLServer.def user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
*/
#include <Windows.h>
#include "MyDLLServer.h"

BOOL WINAPI DLLMAIN(HINSTANCE hDll, DWORD dwReason, LPVOID lpResult) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

extern "C" int SumOfIntegers(int num1, int num2) {
	//code

	int num3 = num1 + num2;
	return num3;
}

