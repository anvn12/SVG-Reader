#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"

class Rectangle {
//private:
public:
	double fillOpacity;
	RGBColor stroke;
	RGBColor fill;
	int strokeWidth;
	Point2D position;
	int width;
	int height;

	Rectangle() {
		fillOpacity = 0;
		//stroke = RGBColor();
		//fill = RGBColor();
		strokeWidth = 0;
		//position = Point2D();
		width = height = 0;
	}

	VOID draw(HDC hdc);
};

#endif
