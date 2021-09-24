#pragma once
class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; // pure virtual function
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; // pure virtual function
};

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; // pure virtual function
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // pure virtual function
};

// CLSID of MultiplicationDivision Component // {6D35C9FC-55F4-42D1-8412-9DECD75BC944}
const CLSID CLSID_MultiplicationDivision = { 0x6d35c9fc, 0x55f4, 0x42d1, 0x84, 0x12, 0x9d, 0xec, 0xd7, 0x5b, 0xc9, 0x44 };

// IID of IMultiplication Interface // {228186FC-F333-4FFB-92A3-CDDF591A6619}
const IID IID_IMultiplication = { 0x228186fc, 0xf333, 0x4ffb, 0x92, 0xa3, 0xcd, 0xdf, 0x59, 0x1a, 0x66, 0x19 };

// IID of IDivision Interface // {72B6BC88-1403-4CF3-B8DD-9B6DBCD3A84C}
const IID IID_IDivision = { 0x72b6bc88, 0x1403, 0x4cf3, 0xb8, 0xdd, 0x9b, 0x6d, 0xbc, 0xd3, 0xa8, 0x4c };

// CLSID of SumSubtract component // {F321F0FA-21C3-464E-9D54-6676049DED14}
const CLSID CLSID_SumSubtract = { 0xf321f0fa, 0x21c3, 0x464e, 0x9d, 0x54, 0x66, 0x76, 0x4, 0x9d, 0xed, 0x14 };

//IID of ISum interface // {7CE7FCD5-B739-4222-95A9-4D90779790F4}
const IID IID_ISum = { 0x7ce7fcd5, 0xb739, 0x4222, 0x95, 0xa9, 0x4d, 0x90, 0x77, 0x97, 0x90, 0xf4 };

//IID of ISubtract interface // {700E5C42-5E33-469C-B7CA-CA94AD7EAC91}
const IID IID_ISubtract = { 0x700e5c42, 0x5e33, 0x469c, 0xb7, 0xca, 0xca, 0x94, 0xad, 0x7e, 0xac, 0x91 };





