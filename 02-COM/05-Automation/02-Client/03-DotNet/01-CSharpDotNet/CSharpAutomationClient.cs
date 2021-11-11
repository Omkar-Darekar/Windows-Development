/*
 * 1. csc.exe /r:AutomationServerTlbForDotNet.dll CSharpAutomationClient.cs
 * 2. Run exe
 */


using System;
using System.Runtime.InteropServices;
using AutomationServerTlbForDotNet;

public class CSharpAutomationClient
{
	public static void Main()
    {
        //Code
        CMyMath objCMyMathClass = new CMyMath();
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;
        int iNum1 = 75, iNum2 = 25, iSum, iSub;
        iSum = objIMyMath.SumOfTwoIntegers(iNum1, iNum2);
        Console.WriteLine("Sum of " + iNum1 + " and " + iNum2 + " is " + iSum);
        iSub = objIMyMath.SubtractionOfTwoIntegers(iNum1, iNum2);
        Console.WriteLine("Subtraction of " + iNum1 + " and " + iNum2 + " is " + iSub);

    }
}

