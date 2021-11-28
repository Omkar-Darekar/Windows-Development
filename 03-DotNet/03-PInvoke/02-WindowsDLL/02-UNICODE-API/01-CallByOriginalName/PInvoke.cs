/*
 * csc.exe PInvoke.cs
 * PInvoke.exe
 */

using System;
using System.Runtime.InteropServices;

public class PInvoke
{
	//code
	[DllImport("user32.dll", CharSet = CharSet.Unicode)]

	//public = naked function dll so public
	//static = file scope, DLL specific
	//extern = Baherun yetat mhanun
	//SDK madhala HWND can import as int in C#
	public static extern int MessageBoxW(int hWnd, String MessageString, String NotificationString, int MB_OK_); //WIN32 MessageBox signature

	public static void Main()
    {
		//code
		MessageBoxW(0, "MessageBox() called as UNICODE API", "WIN32 UNICODE API", 0);
	}
}


