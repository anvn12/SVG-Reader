#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"
#include <sstream>


// inheritance để những cái SVG class có cùng tên
// polymorphism để mỗi hàm trong class làm việc khác nhau
class SVGShape {
public:
	virtual VOID processAttribute(char* attributeName, char* attributeValue) = 0;
	virtual VOID draw(Graphics& graphics) = 0;
};

// inherit 2 public methods
class SVGRectangle : public SVGShape {
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

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics &graphics) override;
};


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
	Point2D cCenter;
	int r;
	RGBColor fill, stroke;
	double strokeWidth, strokeOpacity, fillOpacity;

public:
	SVGCircle() {
		cCenter = Point2D();
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


class SVGEllipse {
private:
	int rx, ry;
	Point2D eCenter;
	RGBColor fill, stroke;
	double strokeWidth, strokeOpacity, fillOpacity;

public:
	SVGEllipse() {
		rx = 0;
		ry = 0;
		eCenter = Point2D();
		fill = RGBColor();
		stroke = RGBColor();
		strokeWidth = 0;
		strokeOpacity = 0;
		fillOpacity = 0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue);
	VOID draw(Graphics& graphics);
};


class SVGLine {
private:  
	Point2D position1, position2;
	RGBColor stroke;  
	double strokeOpacity, strokeWidth; 

public:
	SVGLine() {
		position1 = Point2D();
		position2 = Point2D();
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
