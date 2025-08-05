#include "stdafx.h"
#include "Shape.h"
#include "SVGReader.h"
#include "Transform.h"

//#include "ProcessXML.h"
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


//SVGShape::SVGShape()
//	: position(), stroke(), fill(), 
//		strokeWidth(0.0), strokeOpacity(0.0), fillOpacity(0.0) {}

SVGShape::SVGShape()
	: position(), stroke(), fill(),
	strokeWidth(1.0), strokeOpacity(255.0), fillOpacity(255.0) {
}

VOID SVGShape::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "x") == 0) {
		position.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "y") == 0) {
		position.setY(atof(attributeValue));
	}
	/*else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
	}*/
	else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
		if (strokeOpacity == 0.0) strokeOpacity = 255.0; // Set default if not specified
	}
	/*else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
	}*/
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
		if (fillOpacity == 0.0) fillOpacity = 255.0; // Set default if not specified
	}
	else if (strcmp(attributeName, "stroke-width") == 0) {
		strokeWidth = atof(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-opacity") == 0) {
		// type cast to 255
		strokeOpacity = atof(attributeValue) * 255;
	}
	else if (strcmp(attributeName, "fill-opacity") == 0) {
		// cast to 255 in alpha (argb)
		fillOpacity = atof(attributeValue) * 255;
	}
	else if (strcmp(attributeName, "transform") == 0) {
		transform.parseTransform(attributeValue);
	/*	float tempX = position.getX();
		float tempY = position.getY();
		transform.applyTransform(tempX, tempY);
		position.setX(tempX);
		position.setY(tempY);*/
	}

}

// set transform attribute: translate, rotate, scale
VOID SVGShape::setGraphicsTransform(Graphics& graphics) {
	// + them transform attribute cua svg
	graphics.TranslateTransform(SVGReader::getInstance().getX() /* + transform X*/, SVGReader::getInstance().getY() /* + transform Y*/);
	graphics.ScaleTransform(SVGReader::getInstance().getScale() /* + Scale X */ , SVGReader::getInstance().getScale()) /* + Scale Y */;
	//graphics.RotateTransform(rotate transform);
	//graphics.RotateTransform(45);
}


// Getters
RGBColor SVGShape::getStroke() const {
	return stroke;
}

RGBColor SVGShape::getFill() const {
	return fill;
}

float SVGShape::getStrokeWidth() const {
	return strokeWidth;
}

float SVGShape::getStrokeOpacity() const {
	return strokeOpacity;
}

float SVGShape::getFillOpacity() const {
	return fillOpacity;
}

const Transform& SVGShape::getTransform() const {
	return transform;
}

// Setters
VOID SVGShape::setStroke(const RGBColor& color) {
	stroke = color;
}

VOID SVGShape::setFill(const RGBColor& color) {
	fill = color;
}

VOID SVGShape::setStrokeWidth(float width) {
	strokeWidth = width;
}

VOID SVGShape::setStrokeOpacity(float opacity) {
	strokeOpacity = opacity;
}

VOID SVGShape::setFillOpacity(float opacity) {
	fillOpacity = opacity;
}

VOID SVGShape::setTransform(const Transform& transf) {
	transform = transf;
}



//SVG-Rectangle
VOID SVGRectangle::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "width") == 0) {
		width = atof(attributeValue);
	}
	else if (strcmp(attributeName, "height") == 0) {
		height = atof(attributeValue);
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

//VOID SVGRectangle::draw(Gdiplus::Graphics& graphics) {
//	// set transform attribute: translate, rotate, scale
//	SVGShape::setGraphicsTransform(graphics);
//
//	// argb color
//	Pen pen(Color(255,
//			stroke.getRed(),
//			stroke.getGreen(),
//			stroke.getBlue()),
//			strokeWidth);
//
//	SolidBrush solidBrush(Color((int)fillOpacity,
//						fill.getRed(),
//						fill.getGreen(),
//						fill.getBlue()));
//
//
//	RectF object = RectF(position.getX(), position.getY(),
//						width, height);
//	graphics.FillRectangle(&solidBrush, object);
//
//
//	graphics.DrawRectangle(&pen, object);
//
//	// reset graphics after drawing
//	graphics.ResetTransform();
//}
//
VOID SVGRectangle::draw(Gdiplus::Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	// Apply individual transform
	GraphicsState state = graphics.Save();
	for (const auto& op : getTransform().getOperations()) {
		switch (op.type) {
		case TRANSLATE:
			graphics.TranslateTransform(op.values[0], op.values[1]);
			break;
		case ROTATE:
			if (op.valueCount >= 3) {
				graphics.TranslateTransform(op.values[1], op.values[2]);
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
				graphics.TranslateTransform(-op.values[1], -op.values[2]);
			}
			else {
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
			}
			break;
		case SCALE:
			graphics.ScaleTransform(op.values[0], op.values[1]);
			break;
		}
	}

	// Sử dụng strokeOpacity thay vì hardcode 255
	Pen pen(Color((int)strokeOpacity, stroke.getRed(), stroke.getGreen(), stroke.getBlue()), strokeWidth);
	SolidBrush solidBrush(Color((int)fillOpacity, fill.getRed(), fill.getGreen(), fill.getBlue()));

	RectF object = RectF(position.getX(), position.getY(), width, height);

	// Chỉ draw khi opacity > 0
	if (fillOpacity > 0) {
		graphics.FillRectangle(&solidBrush, object);
	}
	if (strokeOpacity > 0 && strokeWidth > 0) {
		graphics.DrawRectangle(&pen, object);
	}

	graphics.Restore(state);
	graphics.ResetTransform();
}

//SVG-Text
VOID SVGText::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "font-size") == 0) {
		fontSize = atof(attributeValue);
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGText::setContent(char* attributeValue) {
	content = attributeValue;
}

//VOID SVGText::draw(Graphics& graphics) {
//	SVGShape::setGraphicsTransform(graphics);
//
//	SolidBrush brush(Color(255,
//						fill.getRed(),
//						fill.getGreen(),
//						fill.getBlue()));
//
//
//	wstring wideContent(content.begin(), content.end()); //doi sang wstring de gdi+ dung`
//
//
//	FontFamily fontFamily(L"Times New Roman");
//
//
//	Font font(&fontFamily,
//			fontSize,
//			Gdiplus::FontStyleRegular,
//			Gdiplus::UnitPixel);
//
//
//	PointF drawPoint(position.getX(), position.getY());
//
//
//	// can dong cho text
//	/*
//		text__
//		|	  |
//		|_____|
//	*/
//	StringFormat format;
//	format.SetAlignment(Gdiplus::StringAlignmentNear);
//	format.SetLineAlignment(Gdiplus::StringAlignmentFar);
//
//	graphics.DrawString(wideContent.c_str(), -1, &font, drawPoint, &format, &brush);
//
//	graphics.ResetTransform();
//}
VOID SVGText::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	// Apply individual transform
	GraphicsState state = graphics.Save();
	for (const auto& op : getTransform().getOperations()) {
		switch (op.type) {
		case TRANSLATE:
			graphics.TranslateTransform(op.values[0], op.values[1]);
			break;
		case ROTATE:
			if (op.valueCount >= 3) {
				graphics.TranslateTransform(op.values[1], op.values[2]);
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
				graphics.TranslateTransform(-op.values[1], -op.values[2]);
			}
			else {
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
			}
			break;
		case SCALE:
			graphics.ScaleTransform(op.values[0], op.values[1]);
			break;
		}
	}

	// QUAN TRỌNG: Xử lý màu text đúng cách
	// Trong SVG, text ưu tiên fill, nếu không có fill thì dùng stroke
	RGBColor textColor = (fillOpacity > 0) ? fill : stroke;
	float textOpacity = (fillOpacity > 0) ? fillOpacity : strokeOpacity;

	SolidBrush brush(Color((int)textOpacity, textColor.getRed(), textColor.getGreen(), textColor.getBlue()));

	wstring wideContent(content.begin(), content.end());
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	PointF drawPoint(position.getX(), position.getY());

	StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentNear);
	format.SetLineAlignment(Gdiplus::StringAlignmentFar);

	graphics.DrawString(wideContent.c_str(), -1, &font, drawPoint, &format, &brush);

	graphics.Restore(state);
	graphics.ResetTransform();
}


//SVG-Ellipse
VOID SVGEllipse::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "cx") == 0) {
		position.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "cy") == 0) {
		position.setY(atof(attributeValue));
	}
	else if (strcmp(attributeName, "rx") == 0) {
		rx = atof(attributeValue);
	}
	else if (strcmp(attributeName, "ry") == 0) {
		ry = atof(attributeValue);
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

//VOID SVGEllipse::draw(Graphics & graphics) {
//
//	SVGShape::setGraphicsTransform(graphics);
//
//	//int alphaFill = static_cast<int>(fillOpacity * 255);
//	//int alphaStroke = static_cast<int>(strokeOpacity * 255);
//
//	SolidBrush brush(Color(fillOpacity,
//						fill.getRed(), 
//						fill.getGreen(), 
//						fill.getBlue()));
//
//	Pen pen(Color(strokeOpacity,
//				stroke.getRed(),
//				stroke.getGreen(), 
//				stroke.getBlue()), 
//				strokeWidth);
//
//	RectF rectF(position.getX() - rx, position.getY() - ry, 2 * rx, 2 * ry);
//
//
//	graphics.FillEllipse(&brush, rectF);
//	graphics.DrawEllipse(&pen, rectF);
//
//	graphics.ResetTransform();
//}
VOID SVGEllipse::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	// Apply individual transform
	GraphicsState state = graphics.Save();
	for (const auto& op : getTransform().getOperations()) {
		switch (op.type) {
		case TRANSLATE:
			graphics.TranslateTransform(op.values[0], op.values[1]);
			break;
		case ROTATE:
			if (op.valueCount >= 3) {
				graphics.TranslateTransform(op.values[1], op.values[2]);
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
				graphics.TranslateTransform(-op.values[1], -op.values[2]);
			}
			else {
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
			}
			break;
		case SCALE:
			graphics.ScaleTransform(op.values[0], op.values[1]);
			break;
		}
	}

	SolidBrush brush(Color((int)fillOpacity, fill.getRed(), fill.getGreen(), fill.getBlue()));
	Pen pen(Color((int)strokeOpacity, stroke.getRed(), stroke.getGreen(), stroke.getBlue()), strokeWidth);

	RectF rectF(position.getX() - rx, position.getY() - ry, 2 * rx, 2 * ry);

	// Chỉ draw khi opacity > 0
	if (fillOpacity > 0) {
		graphics.FillEllipse(&brush, rectF);
	}
	if (strokeOpacity > 0 && strokeWidth > 0) {
		graphics.DrawEllipse(&pen, rectF);
	}

	graphics.Restore(state);
	graphics.ResetTransform();
}


//SVG-Circle
VOID SVGCircle::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "r") == 0) {
		float r = atof(attributeValue);
		rx = ry = r;
	}
	else {
		SVGEllipse::processAttribute(attributeName, attributeValue);
	}
}

//VOID SVGCircle::draw(Graphics& graphics) {
//	SVGShape::setGraphicsTransform(graphics);
//
//	//// type cast to 255
//	//int alphaFill = static_cast<int>(fillOpacity * 255);
//	//int alphaStroke = static_cast<int>(strokeOpacity * 255);
//
//	SolidBrush brush(Color(fillOpacity,
//		fill.getRed(),
//		fill.getGreen(),
//		fill.getBlue()));
//
//	Pen pen(Color(strokeOpacity,
//		stroke.getRed(),
//		stroke.getGreen(),
//		stroke.getBlue()),
//		strokeWidth);
//
//
//	RectF rectF(position.getX() - rx, position.getY() - rx, 2 * rx, 2 * rx);
//
//
//	graphics.FillEllipse(&brush, rectF);
//	graphics.DrawEllipse(&pen, rectF);
//
//
//	graphics.ResetTransform();
//}


// SAU (đã sửa):
VOID SVGCircle::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	// Apply individual transform
	GraphicsState state = graphics.Save();
	for (const auto& op : getTransform().getOperations()) {
		switch (op.type) {
		case TRANSLATE:
			graphics.TranslateTransform(op.values[0], op.values[1]);
			break;
		case ROTATE:
			if (op.valueCount >= 3) {
				graphics.TranslateTransform(op.values[1], op.values[2]);
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
				graphics.TranslateTransform(-op.values[1], -op.values[2]);
			}
			else {
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
			}
			break;
		case SCALE:
			graphics.ScaleTransform(op.values[0], op.values[1]);
			break;
		}
	}

	SolidBrush brush(Color((int)fillOpacity,
		fill.getRed(),
		fill.getGreen(),
		fill.getBlue()));

	Pen pen(Color((int)strokeOpacity,
		stroke.getRed(),
		stroke.getGreen(),
		stroke.getBlue()),
		strokeWidth);

	// QUAN TRỌNG: Sửa lỗi tọa độ - dùng rx cho cả width và height
	RectF rectF(position.getX() - rx, position.getY() - rx, 2 * rx, 2 * rx);

	// Chỉ draw khi opacity > 0
	if (fillOpacity > 0) {
		graphics.FillEllipse(&brush, rectF);
	}
	if (strokeOpacity > 0 && strokeWidth > 0) {
		graphics.DrawEllipse(&pen, rectF);
	}

	graphics.Restore(state);
	graphics.ResetTransform();
}

//SVG-Line
VOID SVGLine::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "x1") == 0) {
		position1.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "x2") == 0) {
		position2.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "y1") == 0) {
		position1.setY(atof(attributeValue));
	}
	else if (strcmp(attributeName, "y2") == 0) {
		position2.setY(atof(attributeValue));
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGLine::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	// type cast to 255
	//int alphaStroke = static_cast<int>(strokeOpacity * 255);

	Pen pen(Color(strokeOpacity,
				stroke.getRed(), 
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth);

	graphics.DrawLine(&pen, position1.getX(), position1.getY(), position2.getX(), position2.getY());

	graphics.ResetTransform();
}



//SVG-Polyline
VOID SVGPolyline::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "points") == 0) {
		points = attributeValue;
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGPolyline::draw(Graphics& graphics) {
    vector<PointF> pointArray = parsePoints(points);

	if (pointArray.size() < 2) {
        return; 
	}

	SVGShape::setGraphicsTransform(graphics);

	// type cast to 255
    //int alphaFill = static_cast<int>(fillOpacity * 255);
    //int alphaStroke = static_cast<int>(strokeOpacity * 255);

	/*for (auto& pt : pointArray) {
		float x = pt.X, y = pt.Y;

		pt.X = x * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
		pt.Y = y * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();
	}*/

    SolidBrush brush(Color(fillOpacity,
						fill.getRed(), 
						fill.getGreen(), 
						fill.getBlue()));

    Pen pen(Color(strokeOpacity,
				stroke.getRed(), 
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth);


	/*if (fillOpacity > 0 && pointArray.size() >= 3) {
		graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());
	}

	for (size_t i = 0; i < pointArray.size() - 1; i++) {
		graphics.DrawLine(&pen, pointArray[i], pointArray[i + 1]);
	}*/


	// fill
	graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());
	
	// draw
	graphics.DrawLines(&pen, pointArray.data(), pointArray.size());

	graphics.ResetTransform();
}



//SVG-Polygon
VOID SVGPolygon::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "points") == 0) {
		points = attributeValue;
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGPolygon::draw(Graphics& graphics) {
	vector<PointF> pointArray = parsePoints(points);

	if (pointArray.size() < 3) {
		return;
	}

	//for (auto& pt : pointArray) {
	//	float x = pt.X, y = pt.Y;
	//	transform.applyTransform(x, y);
	//	pt.X = x * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
	//	pt.Y = y * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();
	//}


	// type cast to 255
	//int alphaFill = static_cast<int>(fillOpacity * 255);
	//int alphaStroke = static_cast<int>(strokeOpacity * 255);

	SolidBrush brush(Color(fillOpacity,
						fill.getRed(), 
						fill.getGreen(), 
						fill.getBlue()));

	Pen pen(Color(strokeOpacity,
				stroke.getRed(),
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth);


	SVGShape::setGraphicsTransform(graphics);
	//fill 
	graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());

	//stroke oultine
	graphics.DrawPolygon(&pen, pointArray.data(), pointArray.size());

	graphics.ResetTransform();
}


SVGGroup::SVGGroup() {}

SVGGroup::~SVGGroup() {
	for (SVGShape* shape : children) {
		delete shape;
	}
}

//VOID SVGGroup::appendChild(SVGShape* shape) {
//	//noi chung la thang strokeopacity = 0 thi coi nhu thang stroke ko co, fill - fillopacity cung tuong tu
//	if (shape->getStrokeOpacity() == 0.0f) {
//		shape->setStroke(this->getStroke());
//		shape->setStrokeOpacity(this->getStrokeOpacity());
//	}
//	if (shape->getStrokeWidth() == 0.0f) {
//		shape->setStrokeWidth(this->getStrokeWidth());
//	}
//	if (shape->getFillOpacity() == 0.0f) {
//		shape->setFill(this->getFill());
//		shape->setFillOpacity(this->getFillOpacity());
//	}
//
//	children.push_back(shape);
//}

VOID SVGGroup::appendChild(SVGShape* shape) {
	// Chỉ inherit properties từ parent group khi child không có thuộc tính đó
	// VÀ parent group có thuộc tính đó
	if (shape->getStrokeOpacity() == 0.0f && this->getStrokeOpacity() > 0.0f) {
		shape->setStroke(this->getStroke());
		shape->setStrokeOpacity(this->getStrokeOpacity());
	}
	if (shape->getStrokeWidth() == 0.0f && this->getStrokeWidth() > 0.0f) {
		shape->setStrokeWidth(this->getStrokeWidth());
	}
	if (shape->getFillOpacity() == 0.0f && this->getFillOpacity() > 0.0f) {
		shape->setFill(this->getFill());
		shape->setFillOpacity(this->getFillOpacity());
	}

	children.push_back(shape);
}

VOID SVGGroup::processAttribute(char* attributeName, char* attributeValue) {
	SVGShape::processAttribute(attributeName, attributeValue);
}

//VOID SVGGroup::draw(Graphics& graphics) {		//memento design pattern (maybe)
//	GraphicsState state = graphics.Save();	//snapshot trang thai hien tai
//
//	for (const auto& op : getTransform().getOperations()) {		//bien doi
//		switch (op.type) {
//		case TRANSLATE:
//			graphics.TranslateTransform(op.values[0], op.values[1]);
//			break;
//		case ROTATE:
//			graphics.TranslateTransform(op.values[1], op.values[2]);
//			graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
//			graphics.TranslateTransform(-op.values[1], -op.values[2]);
//			break;
//		case SCALE:
//			graphics.ScaleTransform(op.values[0], op.values[1]);
//			break;
//		}
//	}
//
//	for (SVGShape* shape : children) {
//		if (shape) shape->draw(graphics);
//	}
//
//	graphics.Restore(state);	//khoi phuc, tranh anh huong cac group hoac shape khong lien quan
//}

VOID SVGGroup::draw(Graphics& graphics) {
	// Save current graphics state
	GraphicsState groupState = graphics.Save();

	// QUAN TRỌNG: Áp dụng SVG reader transforms trước
	SVGShape::setGraphicsTransform(graphics);

	// Sau đó áp dụng group transforms
	for (const auto& op : getTransform().getOperations()) {
		switch (op.type) {
		case TRANSLATE:
			graphics.TranslateTransform(op.values[0], op.values[1]);
			break;
		case ROTATE:
			// Xử lý rotation với center point chính xác
			if (op.valueCount >= 3) {
				graphics.TranslateTransform(op.values[1], op.values[2]);
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
				graphics.TranslateTransform(-op.values[1], -op.values[2]);
			}
			else {
				// Rotation around origin
				graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
			}
			break;
		case SCALE:
			graphics.ScaleTransform(op.values[0], op.values[1]);
			break;
		}
	}

	// Draw all child shapes
	for (SVGShape* shape : children) {
		if (shape) {
			shape->draw(graphics);
		}
	}

	// Restore original graphics state
	graphics.Restore(groupState);
}