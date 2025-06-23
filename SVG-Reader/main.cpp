#include "stdafx.h"
#include "SVGReader.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	// Use Singleton design pattern as this program is designed to 
	// display 1 image, also it is simple to design. 
	// 
	// If user wants to display more than 1, just launch a new app.
	// 
	// The concept is similar to a web browser tab (it only displays 1 at a time).

	// init GDI+, WNDCLASSEX, HWND,  
	// and show the window
	SVGReader::getInstance().init(hInstance, iCmdShow, "sample.svg");

	// the main loop for processing messages
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	return SVGReader::getInstance().cleanup();
}  // WinMain


