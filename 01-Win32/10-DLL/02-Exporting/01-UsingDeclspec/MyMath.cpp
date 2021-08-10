/*
* cl.exe /c /EHsc MyMath.cpp
* link.exe MyMath.obj /DLL user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS
*/

#include <Windows.h>
#include "MyMath.h"

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}

extern "C" __declspec(dllexport) int MakeCube(int num) {
	//code
	int cube = num * num * num;

	return cube;
}
