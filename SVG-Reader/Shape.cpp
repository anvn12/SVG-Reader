#include "stdafx.h"
#include "Shape.h"

using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID SVGRectangle::processAttribute(char* attributeName, char* attributeValue)
{
	if (strcmp(attributeName, "fill-opacity") == 0) {
		fillOpacity = atof(attributeValue);
	}
	else if (strcmp(attributeName, "x") == 0) {
		position.x = atof(attributeValue);
	}
	else if (strcmp(attributeName, "y") == 0) {
		position.y = atof(attributeValue);
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
	Pen      pen(Color(255, stroke.red, stroke.green, stroke.blue), strokeWidth);

	SolidBrush solidBrush(Color((int)fillOpacity, fill.red, fill.green, fill.blue));

	Rect object = Rect(position.x, position.y, width, height);

	graphics.FillRectangle(&solidBrush, object);
	graphics.DrawRectangle(&pen, object);
}


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
