#include "stdafx.h"
#include "Shape.h"

using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

RGBColor textToRGB(char* text) {
	// rgb(200,200,200)
	// c-style string to string
	string stext = text;
	int r, g, b;
	stext.erase(0, 4);
	stringstream ss(stext);
	string temp;
	getline(ss, temp, ',');
	r = stoi(temp);
	getline(ss, temp, ',');
	g = stoi(temp);
	getline(ss, temp, ')');
	b = stoi(temp);

	return RGBColor(r, g, b);
}

//SVG-Rectangle
VOID SVGRectangle::processAttribute(char* attributeName, char* attributeValue)
{
	if (strcmp(attributeName, "fill-opacity") == 0) {
		fillOpacity = atof(attributeValue);
	}
	else if (strcmp(attributeName, "x") == 0) {
		position.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "y") == 0) {
		position.setY(atof(attributeValue));
	}
	else if (strcmp(attributeName, "width") == 0) {
		width = atoi(attributeValue);
	}
	else if (strcmp(attributeName, "height") == 0) {
		height = atoi(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-width") == 0) {
		strokeWidth = atof(attributeValue);
	}
	else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
	}
}

VOID SVGRectangle::draw(Graphics& graphics) {
	fillOpacity *= 255; // cast to 255 in alpha (argb)
	// argb color
	Pen pen(Color(255, stroke.getRed(), stroke.getGreen(), stroke.getBlue()), strokeWidth);

	SolidBrush solidBrush(Color((int)fillOpacity, fill.getRed(), fill.getGreen(), fill.getBlue()));

	Rect object = Rect(position.getX(), position.getY(), width, height);

	graphics.FillRectangle(&solidBrush, object);
	graphics.DrawRectangle(&pen, object);
}

//SVG-Text
VOID SVGText::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "x") == 0) {
		position.setX(atoi(attributeValue));
	}
	else if (strcmp(attributeName, "y") == 0) {
		position.setY(atoi(attributeValue));
	}
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "font-size") == 0) {
		fontSize = atof(attributeValue);
	}
}

VOID SVGText::setContent(char* attributeValue) {
	content = attributeValue;
}

VOID SVGText::draw(Graphics& graphics)
{
	//ai do lam di
}

//SVG-Circle
VOID SVGCircle::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "cx") == 0) {
		position.setCx(atof(attributeValue));
	}
	else if (strcmp(attributeName, "cy") == 0) {
		position.setCy(atof(attributeValue));
	}
	else if (strcmp(attributeName, "r") == 0) {
		r = atof(attributeValue);
	}
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-width") == 0) {
		strokeWidth = atof(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-opacity") == 0) {
		strokeOpacity = atof(attributeValue);  //  atof, ko phai atoi
	}
	else if (strcmp(attributeName, "fill-opacity") == 0) {
		fillOpacity = atof(attributeValue);  // sua cho nay
	}
}


VOID SVGCircle::draw(Graphics& graphics)
{
	int alphaFill = static_cast<int>(fillOpacity * 255);
	int alphaStroke = static_cast<int>(strokeOpacity * 255);

	SolidBrush brush(Color(alphaFill, fill.getRed(), fill.getGreen(), fill.getBlue()));
	Pen pen(Color(alphaStroke, stroke.getRed(), stroke.getGreen(), stroke.getBlue()), strokeWidth);

	graphics.FillEllipse(&brush,
		static_cast<INT>(position.getCx() - r),
		static_cast<INT>(position.getCy() - r),
		static_cast<INT>(2 * r),
		static_cast<INT>(2 * r));

	graphics.DrawEllipse(&pen,
		static_cast<INT>(position.getCx() - r),
		static_cast<INT>(position.getCy() - r),
		static_cast<INT>(2 * r),
		static_cast<INT>(2 * r));
}


//SVG-Ellipse
//VOID SVGEllipse::processAttribute(char* attributeName, char* attributeValue) {
//	if (strcmp(attributeName, "cx") == 0) {
//		position.setCx(atof(attributeValue));
//	}
//	else if (strcmp(attributeName, "cy") == 0) {
//		position.setCy(atof(attributeValue));
//	}
//	else if (strcmp(attributeName, "rx") == 0) {
//		rx = atof(attributeValue);
//	}
//	else if (strcmp(attributeName, "ry") == 0) {
//		ry = atof(attributeValue);
//	}
//	else if (strcmp(attributeName, "fill") == 0) {
//		fill = textToRGB(attributeValue);
//	}
//	else if (strcmp(attributeName, "stroke") == 0) {
//		stroke = textToRGB(attributeValue);
//	}
//	else if (strcmp(attributeName, "stroke-width") == 0) {
//		strokeWidth = atof(attributeValue);
//	}
//	else if (strcmp(attributeName, "stroke-opacity") == 0) {
//		strokeOpacity = atof(attributeValue);
//	}
//	else if (strcmp(attributeName, "fill-opacity") == 0) {
//		fillOpacity = atoi(attributeValue);
//	}
//}

VOID SVGEllipse::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "cx") == 0) {
		position.setCx(atof(attributeValue));
	}
	else if (strcmp(attributeName, "cy") == 0) {
		position.setCy(atof(attributeValue));
	}
	else if (strcmp(attributeName, "rx") == 0) {
		rx = atof(attributeValue);
	}
	else if (strcmp(attributeName, "ry") == 0) {
		ry = atof(attributeValue);
	}
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-width") == 0) {
		strokeWidth = atof(attributeValue);
	}
	else if (strcmp(attributeName, "stroke-opacity") == 0) {
		strokeOpacity = atof(attributeValue);   
	}
	else if (strcmp(attributeName, "fill-opacity") == 0) {
		fillOpacity = atof(attributeValue);
	}
}


	VOID SVGEllipse::draw(Graphics & graphics)
	{
		int alphaFill = static_cast<int>(fillOpacity * 255);
		int alphaStroke = static_cast<int>(strokeOpacity * 255);

		SolidBrush brush(Color(alphaFill, fill.getRed(), fill.getGreen(), fill.getBlue()));
		Pen pen(Color(alphaStroke, stroke.getRed(), stroke.getGreen(), stroke.getBlue()), strokeWidth);

		RectF rectF(
			position.getCx() - rx,
			position.getCy() - ry,
			2 * rx,
			2 * ry
		);

		graphics.FillEllipse(&brush, rectF);
		graphics.DrawEllipse(&pen, rectF);
	}
