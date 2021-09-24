/*
* Command to compile and link the project
* Compile : cl.exe /c /EHsc ContainmentInnerComponentWithRegFile.cpp
* Link : link.exe ContainmentInnerComponentWithRegFile.obj /DLL /DEF:ContainmentInnerComponentWithRegFile.def user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS
*/
#include<Windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

//class declaration
class CMultiplicationDivision : public IMultiplication, IDivision {
private:
	long m_cRef;
public:
	//constructor
	CMultiplicationDivision(void);
	//destructor
	~CMultiplicationDivision(void);

	//IUknown method declaration
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IMultipllication method declaration
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	//IDivision method declaration
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	//constructor
	CMultiplicationDivisionClassFactory();
	//destructor
	~CMultiplicationDivisionClassFactory();

	// IUknown method declaration
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory method declaration
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global varible declaration
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// DLL Main
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH: break;
	case DLL_PROCESS_DETACH: break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	}
	return(TRUE);
}

//CMultiplicationDivision constructor
CMultiplicationDivision::CMultiplicationDivision(void) {
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//CMultiplicationDivision destructor
CMultiplicationDivision::~CMultiplicationDivision(void) {
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//CMultiplicationDivision IUnknown method
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IMultiplication) {
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision) {
		*ppv = static_cast<IDivision*>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IMultiplication method
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication) {
	//code
	*pMultiplication = num1 * num2;
	return(S_OK);
}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision) {
	//code
	*pDivision = num1 / num2;
	return(S_OK);
}

//Implementation of Class Factory method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void) {
	//code
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void) {
	//code
}

//Implementation of IUnknown method of CMultiplicationDivision ClassFactory

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void) {
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's method
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//Variable declaration
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL) {
		return(CLASS_E_NOAGGREGATION);
	}
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL) {
		return(E_OUTOFMEMORY);
	}

	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock) {
	//code
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return(S_OK);
}

//Implementation of Export function
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	//variable declaration
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	//code
	if (rclsid != CLSID_MultiplicationDivision) {
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL) {
		return(E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0)) {
		return(S_OK);
	}
	else {
		return(S_FALSE);
	}
}

