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

	// set transform attribute: translate, rotate, scale
	VOID setGraphicsTransform(Graphics& graphics);

	// getters
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	float getFillOpacity() const;
	RGBColor getStroke() const;
	RGBColor getFill() const;

	// setters
	void setStrokeWidth(float &width);
	void setStrokeOpacity(float &opacity);
	void setFillOpacity(float &opacity);
	void setStroke(RGBColor &color);
	void setFill(RGBColor& color);
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

	VOID processAttribute(char* attributeName, char* attributeValue) override;

	VOID draw(Graphics& graphics) override;
	
	VOID handleCommand(char cmd, const vector<float>& nums);
};

class SVGGroup : public SVGShape {
private:
	std::vector<SVGShape*> children;

public:
	SVGGroup();
	~SVGGroup();

	void appendChild(SVGShape* shape);

	void processAttribute(char* attributeName, char* attributeValue) override;

	void draw(Gdiplus::Graphics& graphics) override;

	// Getter cho children (neu can)
	const std::vector<SVGShape*>& getChildren() const { return children; }

};

SVGShape* createShapeFromNode(xml_node<>* node) {
	if (!node) return nullptr;

	const char* nodeName = node->name();
	SVGShape* shape = nullptr;

	// Khởi tạo shape tương ứng
	if (strcmp(nodeName, "rect") == 0) shape = new SVGRectangle();
	else if (strcmp(nodeName, "ellipse") == 0) shape = new SVGEllipse();
	else if (strcmp(nodeName, "circle") == 0) shape = new SVGCircle();
	else if (strcmp(nodeName, "text") == 0) shape = new SVGText();
	else if (strcmp(nodeName, "line") == 0) shape = new SVGLine();
	else if (strcmp(nodeName, "polyline") == 0) shape = new SVGPolyline();
	else if (strcmp(nodeName, "polygon") == 0) shape = new SVGPolygon();
	else if (strcmp(nodeName, "g") == 0) shape = new SVGGroup();

	if (!shape) return nullptr;

	// Nếu là text thì set nội dung
	if (auto textShape = dynamic_cast<SVGText*>(shape)) {
		if (node->value()) textShape->setContent(node->value());
	}

	// Parse các attribute
	for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		shape->processAttribute(attr->name(), attr->value());
	}

	// Nếu là group -> đệ quy duyệt con
	if (auto group = dynamic_cast<SVGGroup*>(shape)) {
		for (xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
			SVGShape* childShape = createShapeFromNode(child);
			if (childShape) group->appendChild(childShape);
		}
	}

	return shape;
}

#endif
