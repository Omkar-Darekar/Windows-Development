'''
''' 1. vbc.exe /t:winexe /r:MicrosoftVisualBasic.dll /r:AutomationServerTlbForDotNet.dll VBAutomationClient.vb
''' 

Imports System.Windows.Forms
Imports AutomationServerTlbForDotNet

Public VBAutomationClient
Inherits Form
Public Sub New()
	Dim MyIDispatch As Object
	Dim MyRef As New CMyMathClass
	MyIDispatch MyRef
		Dim iNum1 = 175
	Dim iNum2 = 125
	Dim iSum = MyIDispatch.SumOfTwoIntegers(Num1, Num2)
	Dim str As String = String.Format("Sum Of{0} and {1} is {2}", iNum1, iNum2, iSum)
	MsgBox(str)
	Dim iSub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
	str = String.Format("Sub Of{0} and {1} is {2}", iNum1, iNum2, iSub())
	MsgBox(str)
	End
End Sub

<STAThread()>
Shared Sub Main()
	Application.EnableVisualStyles()
	Application.Run(VBAutomationClient())
End Sub

End Class

