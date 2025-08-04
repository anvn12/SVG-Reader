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
	}

}

// set transform attribute: translate, rotate, scale
VOID SVGShape::setGraphicsTransform(Graphics& graphics) {
	// + them transform attribute cua svg
	transform.applyToGraphics(&graphics);
	
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


	/* can dong cho text

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

VOID SVGEllipse::draw(Graphics & graphics) {
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
	Pen pen(Color(strokeOpacity,
				stroke.getRed(), 
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth);

	graphics.DrawLine(&pen, position1.getX(), position1.getY(), position2.getX(), position2.getY());
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
	graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());
	
	// draw
	graphics.DrawLines(&pen, pointArray.data(), pointArray.size());
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

	SolidBrush brush(Color(fillOpacity,
						fill.getRed(), 
						fill.getGreen(), 
						fill.getBlue()));

	Pen pen(Color(strokeOpacity,
				stroke.getRed(),
				stroke.getGreen(), 
				stroke.getBlue()), 
				strokeWidth);

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
//i need to read and draw this
//<svg xmlns = "http://www.w3.org/2000/svg">
//< path fill = "none" stroke = "rgb(255,0,0)" stroke - width = "5"
//	d = "M100,200 C100,100 250,100 250,200
//	C250, 300 400, 300 400, 200" />
//	< / svg >
VOID SVGPath::draw(Graphics& graphics) {
	GraphicsPath gp;

	PointF current(0, 0); 
	for (auto& cmd : commands) {
		switch (cmd.type) {
		case 'M':
			gp.StartFigure(); //start path
			current = PointF(cmd.data[0].getX(), cmd.data[0].getY());
			break;
		case 'm':
			gp.StartFigure();
			current.X += cmd.data[0].getX();
			current.Y += cmd.data[0].getY();
			break;
		case 'L':
			for (auto& points : cmd.data) {
				PointF point(points.getX(), points.getY());
				gp.AddLine(current, point);
				current = point;
			}
			break;
		case 'l':
			for (auto& points : cmd.data) {
				PointF point(current.X + points.getX(), current.Y + points.getY());
				gp.AddLine(current, point);
				current = point;
			}
			break;
		case 'C':
			for (size_t i = 0; i + 2 < cmd.data.size(); i += 3) { //moi lenh C luon co 3 diem: control 1, control 2, end
				PointF c1(cmd.data[i].getX(), cmd.data[i].getY());
				PointF c2(cmd.data[i + 1].getX(), cmd.data[i + 1].getY());
				PointF endPoint(cmd.data[i + 2].getX(), cmd.data[i + 2].getY());
				gp.AddBezier(current, c1, c2, endPoint);
				current = endPoint;
			}
			break;
		case 'c':
			for (size_t i = 0; i + 2 < cmd.data.size(); i += 3) {
				PointF c1(current.X + cmd.data[i].getX(), current.Y + cmd.data[i].getY());
				PointF c2(current.X + cmd.data[i + 1].getX(),current.Y + cmd.data[i + 1].getY());
				PointF ep(current.X + cmd.data[i + 2].getX(), current.Y + cmd.data[i + 2].getY());
				gp.AddBezier(current, c1, c2, ep);
				current = ep;
			}
			break;
		case 'Z' : case 'z':
			gp.CloseFigure();
			break;
		}
	}

	SolidBrush brush(Color(fillOpacity,
		fill.getRed(),
		fill.getGreen(),
		fill.getBlue()));

	Pen pen(Color(strokeOpacity,
		stroke.getRed(),
		stroke.getGreen(),
		stroke.getBlue()),
		strokeWidth);

	graphics.FillPath(&brush, &gp);
	graphics.DrawPath(&pen, &gp);
}