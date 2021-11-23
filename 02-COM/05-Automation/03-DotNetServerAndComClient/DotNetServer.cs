/*
 * Command to create DLL : csc.exe /t:library DotNetServer.cs
 * to create tlb file : regasm.exe DotNetServer.dll /tlb
 */

using System;

public class DotNetServer
{
	public int SumOfTwoIntegers(int num1, int num2)
    {
        //code
        int num3 = num1 + num2;
        return num3;
    }

    public int SubtractionOfTwoIntegers(int num1, int num2)
    {
        //code
        int num3 = num1 - num2;
        return num3;
    }
}
