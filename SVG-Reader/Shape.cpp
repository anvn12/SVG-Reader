#include "stdafx.h"
#include "Shape.h"
#include "SVGReader.h"
//#include "ProcessXML.h"
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


SVGShape::SVGShape()
	: position(), stroke(), fill(), 
		strokeWidth(0.0), strokeOpacity(0.0), fillOpacity(0.0) {}

VOID SVGShape::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "x") == 0) {
		position.setX(atof(attributeValue));
	}
	else if (strcmp(attributeName, "y") == 0) {
		position.setY(atof(attributeValue));
	}
	else if (strcmp(attributeName, "stroke") == 0) {
		stroke = textToRGB(attributeValue);
	}
	else if (strcmp(attributeName, "fill") == 0) {
		fill = textToRGB(attributeValue);
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
}



//SVG-Rectangle
VOID SVGRectangle::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "width") == 0) {
		width = atoi(attributeValue);
	}
	else if (strcmp(attributeName, "height") == 0) {
		height = atoi(attributeValue);
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGRectangle::draw(Gdiplus::Graphics& graphics) const {
	// argb color
	Pen pen(Color(255,
			stroke.getRed(),
			stroke.getGreen(),
			stroke.getBlue()),
			strokeWidth * SVGReader::getInstance().getScale());

	SolidBrush solidBrush(Color((int)fillOpacity,
						fill.getRed(),
						fill.getGreen(),
						fill.getBlue()));

	float x = position.getX() * SVGReader::getInstance().getScale()
				+ SVGReader::getInstance().getX();

	float y = position.getY() * SVGReader::getInstance().getScale()
				+ SVGReader::getInstance().getY();

	Rect object = Rect(x, y,
						width * SVGReader::getInstance().getScale(),
						height * SVGReader::getInstance().getScale());

	graphics.FillRectangle(&solidBrush, object);
	graphics.DrawRectangle(&pen, object);
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

VOID SVGText::draw(Graphics& graphics) const {
	SolidBrush brush(Color(255,
						fill.getRed(),
						fill.getGreen(),
						fill.getBlue()));

	wstring wideContent(content.begin(), content.end()); //doi sang wstring de gdi+ dung`


	FontFamily fontFamily(L"Times New Roman");


	Font font(&fontFamily,
			fontSize * SVGReader::getInstance().getScale(),
			Gdiplus::FontStyleRegular,
			Gdiplus::UnitPixel);

	float x = position.getX() * SVGReader::getInstance().getScale() 
				+ SVGReader::getInstance().getX();

	float y = position.getY() * SVGReader::getInstance().getScale() 
				+ SVGReader::getInstance().getY();


	PointF drawPoint(x, y);

	//PointF drawPoint(position.getX(), position.getY());


	// can dong cho text
	/*
		text__
		|	  |
		|_____|
	*/
	StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentNear);
	format.SetLineAlignment(Gdiplus::StringAlignmentFar);

	graphics.DrawString(wideContent.c_str(), -1, &font, drawPoint, &format, &brush);
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

VOID SVGEllipse::draw(Graphics & graphics) const {
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
				strokeWidth * SVGReader::getInstance().getScale());

	float scaledRx = rx * SVGReader::getInstance().getScale();
	float scaledRy = ry * SVGReader::getInstance().getScale();

	float x = position.getX() * SVGReader::getInstance().getScale()
				+ SVGReader::getInstance().getX();

	float y = position.getY() * SVGReader::getInstance().getScale()
				+ SVGReader::getInstance().getY();

	RectF rectF(x - scaledRx, y - scaledRy, 2 * scaledRx, 2 * scaledRy);


	graphics.FillEllipse(&brush, rectF);
	graphics.DrawEllipse(&pen, rectF);
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

VOID SVGCircle::draw(Graphics& graphics) const {
	//// type cast to 255
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
		strokeWidth * SVGReader::getInstance().getScale());

	float scaledR = rx * SVGReader::getInstance().getScale();

	float x = position.getX() * SVGReader::getInstance().getScale()
		+ SVGReader::getInstance().getX();

	float y = position.getY() * SVGReader::getInstance().getScale()
		+ SVGReader::getInstance().getY();

	graphics.FillEllipse(&brush, x - scaledR, y - scaledR, 2 * scaledR, 2 * scaledR);
	graphics.DrawEllipse(&pen, x - scaledR, y - scaledR, 2 * scaledR, 2 * scaledR);
}



//SVG-Line
VOID SVGLine::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "x1") == 0) {
		position1.setX(atoi(attributeValue));
	}
	else if (strcmp(attributeName, "x2") == 0) {
		position2.setX(atoi(attributeValue));
	}
	else if (strcmp(attributeName, "y1") == 0) {
		position1.setY(atoi(attributeValue));
	}
	else if (strcmp(attributeName, "y2") == 0) {
		position2.setY(atoi(attributeValue));
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}

VOID SVGLine::draw(Graphics& graphics) const {
	// type cast to 255
	//int alphaStroke = static_cast<int>(strokeOpacity * 255);

	Pen pen(Color(strokeOpacity,
				stroke.getRed(), 
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth * SVGReader::getInstance().getScale());

	float x1 = position1.getX() * SVGReader::getInstance().getScale() 
					+ SVGReader::getInstance().getX();

	float y1 = position1.getY() * SVGReader::getInstance().getScale() 
					+ SVGReader::getInstance().getY();

	float x2 = position2.getX() * SVGReader::getInstance().getScale() 
					+ SVGReader::getInstance().getX();

	float y2 = position2.getY() * SVGReader::getInstance().getScale() 
					+ SVGReader::getInstance().getY();



	graphics.DrawLine(&pen, x1, y1, x2, y2);

	//graphics.DrawLine(&pen, position1.getX(), position1.getY(), position2.getX(), position2.getY());
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

VOID SVGPolyline::draw(Graphics& graphics) const {
    vector<PointF> pointArray = parsePoints(points);

	if (pointArray.size() < 2) {
        return; 
	}

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
				strokeWidth * SVGReader::getInstance().getScale());


    // t quen fill
    if (fillOpacity > 0 && pointArray.size() >= 3) {
        graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());
    }

    for (size_t i = 0; i < pointArray.size() - 1; i++) {
        graphics.DrawLine(&pen, pointArray[i], pointArray[i + 1]);
    }
    
    // graphics.DrawLines(&pen, pointArray.data(), pointArray.size()); ////co the dung cai nay?
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

VOID SVGPolygon::draw(Graphics& graphics) const {
	vector<PointF> pointArray = parsePoints(points);

	if (pointArray.size() < 3) {
		return;
	}

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
				strokeWidth * SVGReader::getInstance().getScale());

	//fill 
	graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());

	//stroke oultine
	graphics.DrawPolygon(&pen, pointArray.data(), pointArray.size());
}


VOID SVGPath::handleCommand(char cmd, const vector<float>& nums) {
	PathCommand command;
	command.type = cmd;
	if (cmd == 'M' || cmd == 'L' || cmd == 'm' || cmd == 'l') {
		for (size_t i = 0; i + 1 < nums.size(); i += 2) { //M 100 100 L 300 100 L 200 300 z, bat dau tu i + 1 de bo qua cai 'M' +=2 do co dau cach
			command.data.push_back(Point2D(nums[i], nums[i + 1]));
		}
	}
	else if (cmd == 'Z' || cmd == 'z') {}
	else {
		return;
	}
}

VOID SVGPath::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "d") == 0) {
		string d(attributeValue);
		stringstream ss;
		char currCmd = '\0';
		float num;
		vector<float> nums;

		//M 100 100 L 300 100 L 200 300 z
		for (size_t i = 0; i < d.size(); i++) {
			char c = d[i];
			if (isalpha(c)) { //la 1 alphabet thi la lenh m c z v, ...
				if (currCmd != '\0') { //xoa lenh truoc do
					handleCommand(currCmd, nums);
					nums.clear();
				}
				currCmd = c;
			}
			else if (isdigit(c) || c == '-' || c == '.' || c == '+') { //M10.5,-20.25L30+40
				ss.str("");
				ss.clear();
				ss << c;
				size_t j = i + 1;
				while (j < d.size() && (isdigit(d[j]) || d[j] == '-' || d[j] == '.' || d[j] == '+')) {
					ss << d[j];
					j++;
				}
				i = j - 1; //ipdate lai pos
				ss >> num;
				nums.push_back(num);
			}
			//gap ' ' hay ',' thi bo qua
		}
		if (currCmd != '\0') {
			handleCommand(currCmd, nums);
		}
	}
	else {
		SVGShape::processAttribute(attributeName, attributeValue);
	}
}