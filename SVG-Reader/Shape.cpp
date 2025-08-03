#include "stdafx.h"
#include "Shape.h"
#include "SVGReader.h"
#include "Transform.h"

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

VOID SVGRectangle::draw(Gdiplus::Graphics& graphics) {
	// set transform attribute: translate, rotate, scale
	SVGShape::setGraphicsTransform(graphics);

	// argb color
	Pen pen(Color(255,
			stroke.getRed(),
			stroke.getGreen(),
			stroke.getBlue()),
			strokeWidth);

	SolidBrush solidBrush(Color((int)fillOpacity,
						fill.getRed(),
						fill.getGreen(),
						fill.getBlue()));


	RectF object = RectF(position.getX(), position.getY(),
						width, height);
	graphics.FillRectangle(&solidBrush, object);


	graphics.DrawRectangle(&pen, object);

	// reset graphics after drawing
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

VOID SVGText::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

	SolidBrush brush(Color(255,
						fill.getRed(),
						fill.getGreen(),
						fill.getBlue()));


	wstring wideContent(content.begin(), content.end()); //doi sang wstring de gdi+ dung`


	FontFamily fontFamily(L"Times New Roman");


	Font font(&fontFamily,
			fontSize,
			Gdiplus::FontStyleRegular,
			Gdiplus::UnitPixel);


	PointF drawPoint(position.getX(), position.getY());


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

VOID SVGEllipse::draw(Graphics & graphics) {

	SVGShape::setGraphicsTransform(graphics);

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

	RectF rectF(position.getX() - rx, position.getY() - ry, 2 * rx, 2 * ry);


	graphics.FillEllipse(&brush, rectF);
	graphics.DrawEllipse(&pen, rectF);

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

VOID SVGCircle::draw(Graphics& graphics) {
	SVGShape::setGraphicsTransform(graphics);

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
		strokeWidth);


	RectF rectF(position.getX() - rx, position.getY() - rx, 2 * rx, 2 * rx);


	graphics.FillEllipse(&brush, rectF);
	graphics.DrawEllipse(&pen, rectF);


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

	// fill
	/*if (fillOpacity > 0 && pointArray.size() >= 3) {
		graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());
	}*/

	/*for (size_t i = 0; i < pointArray.size() - 1; i++) {
		graphics.DrawLine(&pen, pointArray[i], pointArray[i + 1]);
	}*/

	// fill
	graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());

	// draw
	graphics.DrawLines(&pen, pointArray.data(), pointArray.size()); ////co the dung cai nay?

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

	commands.push_back(command);
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
VOID SVGPath::draw(Graphics& graphics) {
	if (commands.empty()) return;

	GraphicsPath path;
	Point2D currentPos(0, 0);
	Point2D pathStart(0, 0);

	for (const auto& cmd : commands) {
		switch (cmd.type) {
		case 'M': // Move absolute
			if (!cmd.data.empty()) {
				currentPos = cmd.data[0];
				pathStart = currentPos;
			}
			break;
		case 'm': // Move relative
			if (!cmd.data.empty()) {
				currentPos.setX(currentPos.getX() + cmd.data[0].getX());
				currentPos.setY(currentPos.getY() + cmd.data[0].getY());
				pathStart = currentPos;
			}
			break;
		case 'L': // Line absolute
			for (const auto& point : cmd.data) {
				float x1 = currentPos.getX(), y1 = currentPos.getY();
				float x2 = point.getX(), y2 = point.getY();

				transform.applyTransform(x1, y1);
				transform.applyTransform(x2, y2);

				x1 = x1 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
				y1 = y1 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();
				x2 = x2 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
				y2 = y2 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();

				path.AddLine(x1, y1, x2, y2);
				currentPos = point;
			}
			break;
		case 'l': // Line relative
			for (const auto& point : cmd.data) {
				float x1 = currentPos.getX(), y1 = currentPos.getY();
				currentPos.setX(currentPos.getX() + point.getX());
				currentPos.setY(currentPos.getY() + point.getY());
				float x2 = currentPos.getX(), y2 = currentPos.getY();

				transform.applyTransform(x1, y1);
				transform.applyTransform(x2, y2);

				x1 = x1 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
				y1 = y1 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();
				x2 = x2 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getX();
				y2 = y2 * SVGReader::getInstance().getScale() + SVGReader::getInstance().getY();

				path.AddLine(x1, y1, x2, y2);
			}
			break;
		case 'Z':
		case 'z': // Close path
			path.CloseFigure();
			currentPos = pathStart;
			break;
		}
	}

	SolidBrush brush(Color((BYTE)fillOpacity,
		fill.getRed(),
		fill.getGreen(),
		fill.getBlue()));

	Pen pen(Color((BYTE)strokeOpacity,
		stroke.getRed(),
		stroke.getGreen(),
		stroke.getBlue()),
		strokeWidth * SVGReader::getInstance().getScale());

	if (fillOpacity > 0) {
		graphics.FillPath(&brush, &path);
	}
	if (strokeWidth > 0 && strokeOpacity > 0) {
		graphics.DrawPath(&pen, &path);
	}
}