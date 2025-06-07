#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"

class rect {
private:
	double fillOpacity;
	Color stroke;
	Color fill;
	int strokeWidth;
	Point position;
	int width;
	int height;
public:
	rect() {
		fillOpacity = 0;
		//stroke = Color();
		//fill = Color();
		strokeWidth = 0;
		position = Point();
		width = height = 0;
	}
};

#endif
