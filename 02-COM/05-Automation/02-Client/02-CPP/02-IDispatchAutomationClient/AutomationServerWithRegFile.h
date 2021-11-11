#pragma once

class IMyMath :public IDispatch {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //Pure virtual function
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // Pure virtual function
};

//CLSID of MyMath Component : // {ED97BB7B-4725-49A3-BA52-2786F39BEBF6}
const CLSID CLSID_MyMath = { 0xed97bb7b, 0x4725, 0x49a3, 0xba, 0x52, 0x27, 0x86, 0xf3, 0x9b, 0xeb, 0xf6 };

//IID of IID_IMyMath Interface : // {BAE60D89-6CCF-4D45-AA76-341B5C3A6599}
const IID IID_IMyMath = { 0xbae60d89, 0x6ccf, 0x4d45, 0xaa, 0x76, 0x34, 0x1b, 0x5c, 0x3a, 0x65, 0x99 };



