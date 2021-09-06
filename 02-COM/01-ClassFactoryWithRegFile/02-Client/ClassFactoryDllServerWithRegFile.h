#pragma once

class ISum : public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual function
};

class ISubtract : public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual function
};

//CLSID of SumSubtract Component  {3BCDC8A9-EDD7-4581-AF98-C2CBA5DAEA9B}
const CLSID CLSID_SumSubtract = {0x3bcdc8a9, 0xedd7, 0x4581, 0xaf, 0x98, 0xc2, 0xcb, 0xa5, 0xda, 0xea, 0x9b};

//IID of ISum Interface // {81002D02-98EA-438E-B42F-A2AFBB3F0068}
const IID IID_ISum = { 0x81002d02, 0x98ea, 0x438e, 0xb4, 0x2f, 0xa2, 0xaf, 0xbb, 0x3f, 0x0, 0x68 };

//IID of ISubtract Interface // {AA188911-7A90-42DB-9F39-ACEC8B529A09}
const IID IID_ISubtract = { 0xaa188911, 0x7a90, 0x42db, 0x9f, 0x39, 0xac, 0xec, 0x8b, 0x52, 0x9a, 0x9 };