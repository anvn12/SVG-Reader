#include "stdafx.h"
#include "SVGReader.h"

#include <shellapi.h>

#include <iostream>

// add hPrevInstance and lpCmdLine (not use these)
// _In_opt_, _In_ int nCmdShow instead of INT iCmdShow
// int WINMAIN instead of INT to ignore the warning
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,
					_In_ int nCmdShow) {
	// Use Singleton design pattern as this program is designed to 
	// display only 1 image, also it is simple to design. 
	// 
	// If user wants to display more than 1, just launch a new app.
	// 
	// The concept is similar to a web browser tab (it only displays 1 at a time).

	// set hInstance and nCmdShow before command line proc
	//because if the command line takes no arguments, it will display
	//to the screen by these 2 variables 
	// 
	//// set the window parameters
	SVGReader::getInstance().setWinParams(hInstance, nCmdShow);


	//=======================
	//// ref: https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-commandlinetoargvw?redirectedfrom=MSDN
	//// command line proc
	//LPWSTR* szArglist;
	//int nArgs;

	//szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	//if (NULL == szArglist) {
	//	wprintf(L"CommandLineToArgvW failed\n");
	//	return 0;
	//}
	//
	//if (nArgs != 2)	{
	//	SVGReader::getInstance().showCmdNoArgumentBox();
	//	return -1;
	//}

	//wstring ws(szArglist[1]);	// buffer variable to convert wstring to string
	//string filename = string(ws.begin(), ws.end());

	//// Free memory allocated for CommandLineToArgvW arguments because the file name is passed to 
	//LocalFree(szArglist);

	// init the program with file name given in command line
	//SVGReader::getInstance().init(filename);
	//=======================


	SVGReader::getInstance().init("D:\\SVG-Reader\\Testcase\\TestCases\\svg-17.svg");

	// the main loop for processing messages
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	return SVGReader::getInstance().cleanup();
}
