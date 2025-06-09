#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"
#include <sstream>

class SVGRectangle {
//private:
public:
	double fillOpacity;
	RGBColor stroke;
	RGBColor fill;
	double strokeWidth;
	Point2D position;
	int width;
	int height;

	SVGRectangle() {
		fillOpacity = 0;
		stroke = RGBColor();
		fill = RGBColor();
		strokeWidth = 0;
		position = Point2D();
		width = height = 0;
	}
	VOID processAttribute(char* attributeName, char* attributeValue);

	VOID draw(Graphics &graphics);
};

class Text {
	int x, y;
	string fill;
	float fontSize;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "x") == 0) x = atoi(value);
		if (strcmp(name, "y") == 0) y = atoi(value);
		if (strcmp(name, "fill") == 0) fill = value;
		if (strcmp(name, "font-size") == 0) fontSize = atof(value);
	}
};

class Circle {
	int cx, cy, r;
	string fill, stroke;
	float strokeWidth, strokeOpacity, fillOpacity;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "cx") == 0) cx = atoi(value);
		if (strcmp(name, "cy") == 0) cy = atoi(value);
		if (strcmp(name, "r") == 0) r = atoi(value);
		if (strcmp(name, "fill") == 0) fill = value;
		if (strcmp(name, "stroke") == 0) stroke = value;
		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
	}
};

class Polyline {
	string fill, stroke, points;
	float strokeWidth, strokeOpacity, fillOpacity;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "fill") == 0) fill = value;
		if (strcmp(name, "stroke") == 0) stroke = value;
		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
		if (strcmp(name, "points") == 0) points = value;
	}
};

class Ellipse {
	int cx, cy, rx, ry;
	string fill, stroke;
	float strokeWidth, strokeOpacity, fillOpacity;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "cx") == 0) cx = atoi(value);
		if (strcmp(name, "cy") == 0) cy = atoi(value);
		if (strcmp(name, "rx") == 0) rx = atoi(value);
		if (strcmp(name, "ry") == 0) ry = atoi(value);
		if (strcmp(name, "fill") == 0) fill = value;
		if (strcmp(name, "stroke") == 0) stroke = value;
		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
	}
};

class Line {
	int x1, x2, y1, y2;
	string stroke;
	float strokeOpacity, strokeWidth;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "x1") == 0) x1 = atoi(value);
		if (strcmp(name, "x2") == 0) x2 = atoi(value);
		if (strcmp(name, "y1") == 0) y1 = atoi(value);
		if (strcmp(name, "y2") == 0) y2 = atoi(value);
		if (strcmp(name, "stroke") == 0) stroke = value;;
		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
	}
};

class Polygon {
	string fill, stroke, points;
	float strokeWidth, strokeOpacity, fillOpacity;

	void processAttribute(const char* name, const char* value) {
		if (strcmp(name, "fill") == 0) fill = value;
		if (strcmp(name, "stroke") == 0) stroke = value;
		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
		if (strcmp(name, "points") == 0) points = value;
	}
};

RGBColor textToRGB(char*);


#endif
