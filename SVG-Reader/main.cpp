#include "stdafx.h"
#include "SVGReader.h"

#include <shellapi.h>

#include <iostream>

// add hPrevInstance and lpCmdLine (not use these)
// _inopt_, _in_
// int nCmdShow instead of INT iCmdShow
// int WINMAIN instead of INT to ignore the warning
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,
					_In_ int nCmdShow) {

	// set the window parameters
	SVGReader::getInstance().setWinParams(hInstance, nCmdShow);

	LPWSTR* szArglist;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nCmdShow);
	if (NULL == szArglist)
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	}
	
	
	if (nCmdShow != 2)
	{
		SVGReader::getInstance().showCmdNoArgumentBox();
		return -1;
	}

	wstring ws(szArglist[1]);
	string myVarS = string(ws.begin(), ws.end());

	SVGReader::getInstance().init(myVarS);


	// Free memory allocated for CommandLineToArgvW arguments.
	LocalFree(szArglist);

	

	// init GDI+, WNDCLASSEX, HWND, and show the window with just the default file name
	// (abstraction)

	// the main loop for processing messages
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	return SVGReader::getInstance().cleanup();






	// Use Singleton design pattern as this program is designed to 
	// display only 1 image, also it is simple to design. 
	// 
	// If user wants to display more than 1, just launch a new app.
	// 
	// The concept is similar to a web browser tab (it only displays 1 at a time).


	// set the window parameters
	SVGReader::getInstance().setWinParams(hInstance, nCmdShow);

	// init GDI+, WNDCLASSEX, HWND, and show the window with just the default file name
	// (abstraction)
	SVGReader::getInstance().init("sample.svg");

	// the main loop for processing messages
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	return SVGReader::getInstance().cleanup();
}
