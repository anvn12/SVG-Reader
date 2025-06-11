#include "stdafx.h"
#include "SVGReader.h"



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	// SINGLETON PATTERN

	// init GDI+, WNDCLASSEX, HWND,  
	// and show the window
	SVGReader::getInstance().init(hInstance, iCmdShow, "sample.svg");

	// the main loop for processing messages
	SVGReader::getInstance().messageLoop();

	// shutdown the gdi+
	return SVGReader::getInstance().cleanup();
}  // WinMain


