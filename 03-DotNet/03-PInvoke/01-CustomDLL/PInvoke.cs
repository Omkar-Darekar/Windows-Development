/*
 * csc.exe PInvoke.cs
 * PInvoke.exe
 */

using System;
using System.Runtime.InteropServices;

public class PInvoke
{
	//code
	[DllImport("MyDLLServer.dll")]

	//public = naked function dll so public
	//static = file scope, DLL specific
	//extern = Baherun yetat mhanun
	public static extern int SumOfIntegers(int n1, int n2);

	public static void Main()
    {
		//code
		int iNum1 = 100;
		int iNum2 = 547;

		int iNum3 = SumOfIntegers(iNum1, iNum2);

		Console.WriteLine("Sum of " + iNum1 + " and " + iNum2 + " is " + iNum3);
	}
}


