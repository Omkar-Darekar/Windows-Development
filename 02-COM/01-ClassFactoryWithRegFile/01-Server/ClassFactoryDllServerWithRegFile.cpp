#include <Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//class declaration 
class CSumSubtract : public ISum, ISubtract {
private:
	long m_cRef;
public:
	CSumSubtract();
	~CSumSubtract();

	HRESULT __stdcall SumOfTwoNumbers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

};

class CSumCubtractClassFactory : public IClassFactory {
private:
	long m_cRef;
public:
	CSumSubtractClassFactory();
	~CSumSubtractClassFactory();

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);

	HRESULT __stdcall QueryResult(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

CSumSubtract::CSumSubtract(void) {
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSumSubtract::SumOfTwoNumbers(int num1, int num2, int* pSum) {
	*pSum = num1 + num2;
	return(S_OK);
}
