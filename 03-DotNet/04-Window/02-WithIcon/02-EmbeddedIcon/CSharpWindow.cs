/*
 * rc.exe CSharpWindow.rc
 * csc.exe /t:winexe /resource:ico.ico /win32res:CSharpWindow.res  CSharpWindow.cs
 */
using System;
using System.Drawing;
using System.Windows.Forms; // Win32 Window is C# Form

public class CSharpWindow : Form
{
	public CSharpWindow() 
	{
		//ICON
		Icon = new Icon(GetType().Assembly.GetManifestResourceStream("ico.ico"));
		//code
		Text = "CSharp Window"; //Caption of the window
		Width = 800; //CreateWindow cha width parameter
		Height = 600; //CreateWindow cha height parameter
		BackColor = Color.Black; //CreateWindow cha HDRBackground parameter
		ResizeRedraw = true; //CreateWindow cha CS_HREDRAW style


		this.KeyDown += new KeyEventHandler(MyKeyDown); //Win32 WM_KEYDOWN
		this.MouseDown += new MouseEventHandler(MyMouseDown); //Win32 WM_LBUTTONDOWN

	}

protected override void OnPaint(PaintEventArgs pea) //Win32 WM_PAINT
{
	//code
	Graphics graphics = pea.Graphics;
	StringFormat string_format = new StringFormat();
	string_format.Alignment = StringAlignment.Center; //Win32 DT_CENTER
	string_format.LineAlignment = StringAlignment.Center; //Win32 DT_VCENTER

	String str = "Hello World !!!";

	graphics.DrawString(str, Font, new SolidBrush(System.Drawing.Color.Green), ClientRectangle/*Win32 GetClientRect*/, string_format);
}


void MyKeyDown(object Sender/*Win32 hWnd*/, KeyEventArgs e/*wParam and lParam*/)
{
		//code
		MessageBox.Show("Some key of keyboard is pressed");
}

void MyMouseDown(object Sender/*Win32 hWnd*/, MouseEventArgs e/*wParam and lParam*/)
{
		//Code
		MessageBox.Show("Some button of mouse is clicked ");
}

public static void Main()
{
	Application.Run(new CSharpWindow());
}
}
