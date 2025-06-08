#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"

class SVGRectangle {
//private:
public:
	double fillOpacity;
	RGBColor stroke;
	RGBColor fill;
	int strokeWidth;
	Point2D position;
	int width;
	int height;

	SVGRectangle() {
		fillOpacity = 0;
		//stroke = RGBColor();
		//fill = RGBColor();
		strokeWidth = 0;
		//position = Point2D();
		width = height = 0;
	}
	VOID processAttribute(char* attributeName, char* attributeValue);

	VOID draw(Graphics &graphic);
};

#endif
