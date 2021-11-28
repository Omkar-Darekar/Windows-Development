/*
 * csc.exe PInvoke.cs
 * PInvoke.exe
 */

using System;
using System.Runtime.InteropServices;

public class PInvoke
{
	//code
	[DllImport("user32.dll")]

	//public = naked function dll so public
	//static = file scope, DLL specific
	//extern = Baherun yetat mhanun
	//SDK madhala HWND can import as int in C#
	public static extern int MessageBoxA(int hWnd, String MessageString, String NotificationString, int MB_OK_); //WIN32 MessageBox signature

	public static void Main()
    {
		//code
		MessageBoxA(0, "MessageBox() called as ANSI API", "WIN32 ANSI API", 0);
	}
}


