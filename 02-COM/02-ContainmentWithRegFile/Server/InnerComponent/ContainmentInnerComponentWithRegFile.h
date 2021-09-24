#pragma once
class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MultiplicationDivision Component // {6D35C9FC-55F4-42D1-8412-9DECD75BC944}
const CLSID CLSID_MultiplicationDivision = { 0x6d35c9fc, 0x55f4, 0x42d1, 0x84, 0x12, 0x9d, 0xec, 0xd7, 0x5b, 0xc9, 0x44 };

// IID of IMultiplication Interface // {228186FC-F333-4FFB-92A3-CDDF591A6619}
const IID IID_IMultiplication = { 0x228186fc, 0xf333, 0x4ffb, 0x92, 0xa3, 0xcd, 0xdf, 0x59, 0x1a, 0x66, 0x19 };

// IID of IDivision Interface // {72B6BC88-1403-4CF3-B8DD-9B6DBCD3A84C}
const IID IID_IDivision = { 0x72b6bc88, 0x1403, 0x4cf3, 0xb8, 0xdd, 0x9b, 0x6d, 0xbc, 0xd3, 0xa8, 0x4c };


