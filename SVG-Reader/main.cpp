#include "stdafx.h"
#include "SVGReader.h"


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	// init the variable with 2 arguments
	SVGReader svgreader;

	// init GDI+, WNDCLASSEX, HWND,  
	// and show the window
	svgreader.init(hInstance, iCmdShow);

	// the main loop for processing messages
	svgreader.messageLoop();

	// shutdown the gdi+
	return svgreader.cleanup();
}  // WinMain


