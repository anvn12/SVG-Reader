#include "stdafx.h"
#include "Shape.h"

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
	//if (strcmp(attributeName, "stroke") == 0) stroke = attributeValue;
	//if (strcmp(attributeName, "fill") == 0) fill = value;
}

