/*
* Code type -> c++/cx : C++ Component Extension
* Compile -> cl.exe /c /EHsc /ZW HelloWorld.cpp
* link -> link.exe HelloWorld.obj /SUBSYSTEM:CONSOLE
* 
* compile and link -> cl.exe /EHsc /ZW HelloWorld.cpp /link vccorlib.lib runtimeobject.lib /SUBSYSTEM:CONSOLE
*/

#include<iostream> //for insertion operation and endl used iostream. 

using namespace Platform; //used for hat(^) and Array and String 
using namespace std; //used for wcout


int main(Array<String^>^ args) {
	//code
	String^ str = "Hello World!!!";
	wcout << str->Data() << endl;
	
	return 0;
}


