#include "stdafx.h"
#include "Shape.h"

VOID SVGRectangle::processAttribute(char* attributeName, char* attributeValue)
{
	if (attributeName == "fill-opacity") {
		fillOpacity = atoi(attributeValue);
	}
	else if (attributeName == "x") {
		position.x = atoi(attributeValue);
	}
	else if (attributeName == "y") {
		position.y = atoi(attributeValue);
	}
}

