#ifndef Shape_h
#define Shape_h
#pragma once

#include "General.h"
#include "Transform.h"
#include <sstream>

class SVGShape;
class SVGGroup;
SVGShape* createShapeFromNode(xml_node<>* node);
SVGShape* createShapeFromNode(xml_node<>* node, SVGGroup* groupParent);


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
	SVGShape(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity) 
		: stroke(_stroke), strokeWidth(_strokeWidth), strokeOpacity(_strokeOpacity), 
		fill(_fill), fillOpacity(_fillOpacity) {
	}
	virtual ~SVGShape() = default;


	// process SVGShape common attributes
	virtual VOID processAttribute(char* attributeName, char* attributeValue);

	// each shape has distinct draw function -> pure virtual
	// (abstract class)
	virtual VOID draw(Graphics& graphics) = 0;

	// set transform attribute: translate, rotate, scale
	VOID setGraphicsTransform(Graphics& graphics);

	// getters
	float getStrokeWidth() const { return strokeWidth; }
	float getStrokeOpacity() const { return strokeOpacity; }
	float getFillOpacity() const { return fillOpacity; }
	RGBColor getStroke() const { return stroke; }
	RGBColor getFill() const { return fill; }

	// setters
	void setStrokeWidth(const float &width) { strokeWidth = width; }
	void setStrokeOpacity(const float &opacity) { strokeOpacity = opacity; }
	void setFillOpacity(const float &opacity) { fillOpacity = opacity; }
	void setStroke(const RGBColor &color) { stroke = color; }
	void setFill(const RGBColor& color) { fill = color; }
	

};



// inherit 2 public methods
class SVGRectangle : public SVGShape {
private:
	int width, height;
public:
	SVGRectangle() : SVGShape(), width(0), height(0) {}

	SVGRectangle(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity), width(0), height(0) {
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics &graphics) override;
};



class SVGText : public SVGShape {
private:
	float fontSize;
	string content;
public:
	SVGText() : SVGShape(), fontSize(0.0) {}

	SVGText(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity), fontSize(0.0) {
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID setContent(char* attributeValue);

	VOID draw(Graphics& graphics) override;
};



class SVGEllipse : public SVGShape {
protected:
	int rx, ry;
public:
	SVGEllipse() : SVGShape(), rx(0), ry(0) {}

	SVGEllipse(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity), rx(0), ry(0) {
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};



class SVGCircle : public SVGEllipse {
public:
	SVGCircle() : SVGEllipse() {
		rx = ry = 0;
	}

	SVGCircle(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGEllipse(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity) {
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

	SVGLine(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity), position1(), position2() {
	}

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

	SVGPolyline(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity) {
		points = "";
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

	SVGPolygon(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity) {
		points = "";
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;
	VOID draw(Graphics& graphics) override;
};

struct PathCommand {
	char type; // 'M', 'L', 'C', 'Z', 'H', 'V'
	vector<Point2D> data; //for x,y and control points
};

class SVGPath : public SVGShape {
private:
	vector<PathCommand> commands;
public:
	SVGPath() : SVGShape() {
		strokeOpacity = 255.0; 
		fillOpacity = 255.0;
	}

	SVGPath(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity) {
	}

	VOID processAttribute(char* attributeName, char* attributeValue) override;

	VOID draw(Graphics& graphics) override;
	
	VOID handleCommand(char cmd, const vector<float>& nums);
};

class SVGGroup : public SVGShape {
private:
	std::vector<SVGShape*> children;

public:
	SVGGroup() {}

	SVGGroup(const RGBColor& _stroke, const float& _strokeWidth,
		const float& _strokeOpacity, const RGBColor& _fill, const float& _fillOpacity)
		: SVGShape(_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity) {
	}

	~SVGGroup() {
		for (SVGShape* shape : children) {
			delete shape;
		}
	}

	void appendChild(SVGShape* shape);

	void processAttribute(char* attributeName, char* attributeValue) override {
		SVGShape::processAttribute(attributeName, attributeValue);
	}

	void draw(Gdiplus::Graphics& graphics) override;

	// Getter cho children (neu can)
	const std::vector<SVGShape*>& getChildren() const { return children; }

};



#endif
