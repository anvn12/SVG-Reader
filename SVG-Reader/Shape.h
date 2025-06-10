#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"
#include <sstream>

class SVGRectangle {
private:
	double fillOpacity;
	RGBColor stroke;
	RGBColor fill;
	double strokeWidth;
	Point2D position;
	int width;
	int height;

public:
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

//class Text {
//	int x, y;
//	string fill;
//	float fontSize;
//
//	void processAttribute(const char* name, const char* value) {
//		if (strcmp(name, "x") == 0) x = atoi(value);
//		if (strcmp(name, "y") == 0) y = atoi(value);
//		if (strcmp(name, "fill") == 0) fill = value;
//		if (strcmp(name, "font-size") == 0) fontSize = atof(value);
//	}
//};

class SVGText {
private:
	Point2D position;
	RGBColor fill;
	double fontSize;
	string content;

public:
	SVGText() {
		position = Point2D();
		fill = RGBColor();
		fontSize = 0;
	}
	VOID processAttribute(char* attributeName, char* attributeValue);
	VOID setContent(char* attributeValue);

	VOID draw(Graphics& graphics);
};

class SVGCircle {
private:
	Point2D position;
	float r;
	RGBColor fill, stroke;
	double strokeWidth, strokeOpacity, fillOpacity;

public:
	SVGCircle() {
		position = Point2D();
		r = 0;
		fill = RGBColor();
		stroke = RGBColor();
		strokeWidth = 0;
		fillOpacity = 0;
		strokeOpacity = 0;
	}
	VOID processAttribute(char* attributeName, char* attributeValue);

	VOID draw(Graphics& graphics);
};

//class Circle {
//	int cx, cy, r;
//	string fill, stroke;
//	float strokeWidth, strokeOpacity, fillOpacity;
//
//	void processAttribute(const char* name, const char* value) {
//		if (strcmp(name, "cx") == 0) cx = atoi(value);
//		if (strcmp(name, "cy") == 0) cy = atoi(value);
//		if (strcmp(name, "r") == 0) r = atoi(value);
//		if (strcmp(name, "fill") == 0) fill = value;
//		if (strcmp(name, "stroke") == 0) stroke = value;
//		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
//		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
//		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
//	}
//};

//lam polyline di

class SVGEllipse {
private:
	float rx, ry;
	Point2D position;
	RGBColor fill, stroke;
	double strokeWidth, strokeOpacity, fillOpacity;

public:
	SVGEllipse() {
		rx = 0;
		ry = 0;
		position = Point2D();
		fill = RGBColor();
		stroke = RGBColor();
		strokeWidth = 0;
		strokeOpacity = 0;
		fillOpacity = 0;
	}
	VOID processAttribute(char* attributeName, char* attributeValue);

	VOID draw(Graphics& graphics);
};

//class Ellipse {
//	int cx, cy, rx, ry;
//	string fill, stroke;
//	float strokeWidth, strokeOpacity, fillOpacity;
//
//	void processAttribute(const char* name, const char* value) {
//		if (strcmp(name, "cx") == 0) cx = atoi(value);
//		if (strcmp(name, "cy") == 0) cy = atoi(value);
//		if (strcmp(name, "rx") == 0) rx = atoi(value);
//		if (strcmp(name, "ry") == 0) ry = atoi(value);
//		if (strcmp(name, "fill") == 0) fill = value;
//		if (strcmp(name, "stroke") == 0) stroke = value;
//		if (strcmp(name, "stroke-width") == 0) strokeWidth = atof(value);
//		if (strcmp(name, "stroke-opacity") == 0) strokeOpacity = atof(value);
//		if (strcmp(name, "fill-opacity") == 0) fillOpacity = atoi(value);
//	}
//};

class SVGLine {
private:  
	int x1, x2, y1, y2;
	RGBColor stroke;  
	double strokeOpacity, strokeWidth; 

public:
	SVGLine() {
		x1 = x2 = y1 = y2 = 0;
		stroke = RGBColor();
		strokeOpacity = 1.0;
		strokeWidth = 1.0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue);  
	VOID draw(Graphics& graphics);
};

class SVGPolyline {
private:  
	RGBColor fill, stroke;  
	string points;
	double strokeWidth, strokeOpacity, fillOpacity; 

public:
	SVGPolyline() {
		fill = RGBColor();
		stroke = RGBColor();
		points = "";
		strokeWidth = 1.0;
		strokeOpacity = 1.0;
		fillOpacity = 1.0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue);  
	VOID draw(Graphics& graphics);
};



class SVGPolygon {
private: 
	RGBColor fill, stroke;  
	string points;
	double strokeWidth, strokeOpacity, fillOpacity;  

public:
	SVGPolygon() {
		fill = RGBColor();
		stroke = RGBColor();
		points = "";
		strokeWidth = 1.0;
		strokeOpacity = 1.0;
		fillOpacity = 1.0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue);  
	VOID draw(Graphics& graphics);
};

RGBColor textToRGB(char*);


#endif
