#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"
#include "Transform.h"
#include <sstream>


// inheritance để những cái SVG class có cùng tên
// polymorphism để mỗi hàm trong class làm việc khác nhau
class SVGShape {
protected:
	Transform transform;
	Point2D position;
	RGBColor stroke, fill;
	float strokeWidth, strokeOpacity, fillOpacity;
public:
	SVGShape();
	virtual ~SVGShape() = default;


	// process SVGShape common attributes
	virtual VOID processAttribute(char* attributeName, char* attributeValue);

	// each shape has distinct draw function -> pure virtual
	// (abstract class)
	virtual VOID draw(Graphics& graphics) = 0;

	VOID setGraphicsTransform(Graphics& graphics);
};



// inherit 2 public methods
class SVGRectangle : public SVGShape {
private:
	int width, height;
public:
	SVGRectangle() : SVGShape(), width(0), height(0) {}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics &graphics) override;
};



class SVGText : public SVGShape {
private:
	float fontSize;
	string content;
public:
	SVGText() : SVGShape(), fontSize(0.0) {}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID setContent(char* attributeValue);

	VOID draw(Graphics& graphics) override;
};



class SVGEllipse : public SVGShape {
protected:
	int rx, ry;
public:
	SVGEllipse() : SVGShape(), rx(0), ry(0) {}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};



class SVGCircle : public SVGEllipse {
public:
	SVGCircle() : SVGEllipse() {
		rx = ry = 0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};



class SVGLine : public SVGShape {
private:  
	Point2D position1, position2;

public:
	SVGLine() : SVGShape(), position1(), position2() {}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};



class SVGPolyline : public SVGShape {
private: 
	string points;
public:
	SVGPolyline() : SVGShape() {
		points = "";
		fillOpacity = 1.0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};



class SVGPolygon : public SVGShape {
private: 
	string points;
public:
	SVGPolygon() : SVGShape() {
		points = "";
		strokeWidth = 1.0;
		strokeOpacity = 1.0;
		fillOpacity = 1.0;
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};

struct PathCommand {
	char type; // 'M', 'L', 'C', 'Z'
	vector<Point2D> data; //for x,y and control points
};

class SVGPath : public SVGShape {
private:
	vector<PathCommand> commands;
public:
	SVGPath() : SVGShape() {}

	VOID processAttribute(char* attributeName, char* attributeValue) override;

	VOID draw(Graphics& graphics) override;
	
	VOID handleCommand(char cmd, const vector<float>& nums);
};

#endif
