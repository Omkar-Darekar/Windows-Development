/*
* To compile 
* 1. cl.exe /c /EHsc AutomationServerWithRegFile.cpp
* 2. link.exe AutomationServerWithRegFile.obj /DLL /DEF:AutomationServerWithRegFile.def user32.lib gdi32.lib ole32.lib oleaut32.lib
*/

/*Header File*/
#include<Windows.h>
#include<stdio.h>
#include "AutomationServerWithRegFile.h"


/*Global Variable Declaration*/
long glNumberOfActiveComponents = 0; // Number of active components
long glNumberOfServerLocks = 0; //Number of server lock
//LIBID_AutomationServer // {1BCB8B43-75F4-4C33-ACAE-ECE695567A54}
const GUID LIBID_AutomationServer = { 0x1bcb8b43, 0x75f4, 0x4c33, 0xac, 0xae, 0xec, 0xe6, 0x95, 0x56, 0x7a, 0x54 };

/*//Class Declaration
  //Concreate Class */
class CMyMath :public IMyMath {
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;

public:
	//constructor
	CMyMath(void);
	//destructor
	~CMyMath();

	//IUnknown Methods (Inherited from IDispatch)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch Method Declaration (Inherited from IMyMath)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	//IMyMath Methods
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//Custom Method
	HRESULT InitInstance(void);

};

//IClass Factory
class CMyMathClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	//Constructor
	CMyMathClassFactory(void);
	//Destructor
	~CMyMathClassFactory(void);

	//IUnknown Methods (Inherited from IClassFactory)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory Method (Inherited from CMyMathClassFactory)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//DLL Main
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	//code
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
	return(TRUE);
}

//CMyMath Constructor
CMyMath::CMyMath(void) {
	//code
	m_cRef = 1; //Hardcodded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //Increment Global Counter
	m_pITypeInfo = NULL; // Private variable initializing to NULL
}

CMyMath::~CMyMath(void) {
	//Code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Implementation of CMyMath IUnknown Method
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv) {
	//code
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IDispatch) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IMyMath) {
		*ppv = static_cast<IMyMath*>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMath::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CMyMath IDispatch Method
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo) {
	//code 
	*pCountTypeInfo = 1;
	return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo) {
	//code
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0) {
		return(DISP_E_BADINDEX);
	}
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId) {
	//code
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExceptInfo, UINT* puArgErr) {

	//code
	return(DispInvoke(this, m_pITypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExceptInfo, puArgErr));
}

//IMyMath Methods
HRESULT CMyMath::SumOfTwoIntegers(int iNum1, int iNum2, int* pSum) {
	//code
	*pSum = iNum1 + iNum2;
	return(S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int iNum1, int iNum2, int* pSub) {
	//code
	*pSub = iNum1 - iNum2;
	return(S_OK);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr) {
	//variable declaration
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	//code
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr)) {
		hr = HRESULT_CODE(hr);
	}
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0) {
		//swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		MessageBox(hwnd, TEXT("Inside FormatMessage"), TEXT("COM Error"), MB_OK);
		LocalFree(szErrorMessage);
	}
	else {
		//swprintf_s(str, TEXT("Could Not Find Description of Error # % #x"), hr);
		MessageBox(hwnd, TEXT("Could Not Find Description of Error"), TEXT("COM Error"), MB_OK);
	}

	//MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

HRESULT CMyMath::InitInstance(void) {
	//Function Declaration (To convert com error in human redable format)
	void ComErrorDescriptionString(HWND, HRESULT);

	//Variable Declaration
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	//code
	if (m_pITypeInfo == NULL) {
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0, // Major and Minor Version
			0x00, //LANG_NEUTRAL
			&pITypeLib); 
		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}

/*IClass Factory Method*/

//CMyMathClassFactory Methods
//Constructor
CMyMathClassFactory::CMyMathClassFactory(void) {
	//code
	m_cRef = 1; //Hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Destructor
CMyMathClassFactory::~CMyMathClassFactory(void) {
	//code
}

//IClassFactory's IUnknown Method Implementation
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CMyMathClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//IClassFactory Methods
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
	//variable declaration
	CMyMath* pCMyMath = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL) {
		MessageBox(NULL, TEXT("CLASS_E_NOAGGREGATION"), TEXT("Error"), MB_OK);
		return(CLASS_E_NOAGGREGATION);
	}

	//Create the instance of component i.e. CMath class
	pCMyMath = new CMyMath;

	if (pCMyMath == NULL) {
		MessageBox(NULL, TEXT("E_OUTOFMEMORY"), TEXT("Error"), MB_OK);
		return(E_OUTOFMEMORY);
	}

	//call automation related init method
	pCMyMath->InitInstance();

	//get the requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock) {
	//code
	if (fLock) {
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else {
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return(S_OK);
}


//Implementation of Exported Function From This Dll

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
	//Variable declaration
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;

	//code
	if (rclsid != CLSID_MyMath) {
		MessageBox(NULL, TEXT("DllGetClassObject : CLSID_MyMath : CLASS_E_CLASSNOTAVAILABLE"), TEXT("Error"), MB_OK);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	//create class factory
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL) {
		MessageBox(NULL, TEXT("DllGetClassObject : CLSID_MyMath : OK"), TEXT("Error"), MB_OK);
		return(E_OUTOFMEMORY);
	}
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
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




