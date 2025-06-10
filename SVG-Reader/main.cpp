#include "stdafx.h"
#include "SVGReader.h"



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	// SINGLETON PATTERN
	//SVGReader& svgreader = SVGReader::getInstance();

	// init GDI+, WNDCLASSEX, HWND,  
	// and show the window
	//svgreader.init(hInstance, iCmdShow);
	SVGReader::getInstance().init(hInstance, iCmdShow);

	// the main loop for processing messages
	//svgreader.messageLoop();
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	//return svgreader.cleanup();
	return SVGReader::getInstance().cleanup();
}  // WinMain


