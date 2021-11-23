/*
* To compile and linl : cl.exe /clr ManagedCpp.cpp
* CPP native and C# combine code
*/
#include<stdio.h>
#using<mscorlib.dll>
using namespace System;

int main(void) {
	//code
	printf("This line is printf()\n");
	Console::WriteLine("This line is printed by WriteLine() in console type\n");
	return 0;
}
