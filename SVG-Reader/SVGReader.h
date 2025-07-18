#ifndef SVGReader_h
#define SVGReader_h
#pragma once

#include "resource.h"
#include "Shape.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>


class SVGReader {
private:
	// these two proc functions deal private variables (like changing value...)
	// so they are two friend functions
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);
	friend LRESULT CALLBACK DlgProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);


	HINSTANCE hInstance = NULL;
	INT nCmdShow = 0;

	// GDI+ variables
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	
	HWND hWnd = 0;

	MSG msg;	// messages

	// store current opening file name and shapes
	string curFileName;
	vector<SVGShape*> shapes;

	// move and zoom objects
	int x = 0, y = 0;
	float scale = 1;


	// Singleton pattern -> constructors and destructors are private
	// 
	// already had setWinParams and init to initialize variables
	SVGReader() {}

	// there is only 1 SVGReader in the whole
	// program, so no copy or assign the SVGReader
	SVGReader(const SVGReader&) = delete;
	SVGReader& operator=(const SVGReader&) = delete;

	// already had the cleanUp() function to clean things
	~SVGReader() { cleanup(); }
public:
	// get access to the only 1 SVGReader in the program
	static SVGReader& getInstance();


	// set the hInstance and nCmdShow of WinMain
	void setWinParams(HINSTANCE hInstance, INT nCmdShow);

	// init, main loop, clean up functions
	void init(std::string fileName);
	void messageLoop();
	INT cleanup();

	// clear the shapes vector (it contains allocated pointers)
	void clearShapes();


	// getter and setter
	int getX() const { return x; }
	int getY() const { return y; }

	float getScale() const { return scale; }
	void setScale(float val);


	// open file in menu bar to get the file name
	void openFile();

	// extract xml components and their attributes 
	// store in vector<SVGShape*> shapes 
	void processXML();



	// to render all shapes
	void render(Graphics& graphics);
};

#endif