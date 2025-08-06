#include "stdafx.h"
#include "Shape.h"
#include "SVGReader.h"
#include "Transform.h"
#include <algorithm>

//#include "ProcessXML.h"
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

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
	else if (strcmp(nodeName, "path") == 0) shape = new SVGPath();
	else if (strcmp(nodeName, "g") == 0) shape = new SVGGroup();
	// undefined SVG shape -> do nothing

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
			SVGShape* childShape = createShapeFromNode(child, group);
			if (childShape) group->appendChild(childShape);
		}
	}

	return shape;
}

SVGShape* createShapeFromNode(xml_node<>* node, SVGGroup* groupParent) {
	if (!node) return nullptr;

	const char* nodeName = node->name();
	SVGShape* shape = nullptr;

	// them mấy cái constructor vô -> thay vì new thì new + thuộc tính của groupParent
	// // nếu ở dưới có xử lí thêm thuộc tính -> thuộc tính parent mất đi
	//groupParent->getFill()/
	//_stroke, _strokeWidth, _strokeOpacity, _fill, _fillOpacity

	// Khởi tạo shape tương ứng
	if (strcmp(nodeName, "rect") == 0) shape = new SVGRectangle(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "ellipse") == 0) shape = new SVGEllipse(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "circle") == 0) shape = new SVGCircle(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "text") == 0) shape = new SVGText(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "line") == 0) shape = new SVGLine(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "polyline") == 0) shape = new SVGPolyline(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "polygon") == 0) shape = new SVGPolygon(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "path") == 0) shape = new SVGPath(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	else if (strcmp(nodeName, "g") == 0) shape = new SVGGroup(groupParent->getStroke(),
		groupParent->getStrokeWidth(), groupParent->getStrokeOpacity(), groupParent->getFill(), groupParent->getFillOpacity());
	// undefined SVG shape -> do nothing

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
			SVGShape* childShape = createShapeFromNode(child, group);
			if (childShape) group->appendChild(childShape);
		}
	}

	return shape;
}

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
		if (strcmp(attributeValue, "none") == 0) {
			strokeOpacity = 0.0; 
		}
		else {
			stroke = textToRGB(attributeValue);
		}
	}
	else if (strcmp(attributeName, "fill") == 0) {
		if (strcmp(attributeValue, "none") == 0) {
			fillOpacity = 0.0;  
		}
		else {
			fill = textToRGB(attributeValue);
		}
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
	// undefined attributes -> do nothing
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

	// add some variables to fix the alignment in gdi+
	int ascent = fontFamily.GetCellAscent(FontStyleRegular);
	int emHeight = fontFamily.GetEmHeight(FontStyleRegular);
	float lineHeight = fontSize; // line height
	float baselineOffset = lineHeight * (float) ascent / emHeight;

	
	/* can dong cho text

		text__
		|	  |
		|_____|
	*/
	StringFormat format;
	//format.SetLineAlignment(Gdiplus::StringAlignmentFar); xxxxxxxxxx
	// 
	format.SetAlignment(Gdiplus::StringAlignmentNear); // Left aligned
	format.SetLineAlignment(StringAlignmentNear);


	// cho này đang gặp vấn đề: cái - baseline/2 là chỉnh bừa chứ ko có logic gì??
	PointF drawPoint(position.getX() - baselineOffset / 2, position.getY() - baselineOffset);



	//graphics.DrawString(wideContent.c_str(), -1, &font, drawPoint, &format, &brush);


	// as gdi+ does not support draw text with stroke -> use path
	// ref: https://www.codeproject.com/Articles/42529/Outline-Text

	GraphicsPath path;
	path.AddString(wideContent.c_str(), -1, &fontFamily,
		Gdiplus::FontStyleRegular, fontSize, drawPoint, &format);



	Pen pen(Color(strokeOpacity,
		stroke.getRed(),
		stroke.getGreen(),
		stroke.getBlue()),
		strokeWidth);

	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
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
		if (nums.size() >= 2) {
			command.data.push_back(Point2D(nums[0], nums[1]));
			commands.push_back(command);
			//xu ly cac truong hop nhu m50 100 100 100 nghia la co line bat dau tu 50,100 den 100,100 du 0 co L/l
			if (nums.size() > 2) {
				PathCommand lineCommand;
				lineCommand.type = (cmd == 'M') ? 'L' : 'l'; 
				for (size_t i = 2; i + 1 < nums.size(); i += 2) {
					lineCommand.data.push_back(Point2D(nums[i], nums[i + 1]));
				}
				commands.push_back(lineCommand);
			}
		}
		return;
    }
	else if (cmd == 'H' || cmd == 'h') { //h80v60
		command.data.push_back(Point2D(nums[0], 0));
	}
	else if (cmd == 'V' || cmd == 'v') {
		command.data.push_back(Point2D(0, nums[0]));
	}
	else if (cmd == 'C' || cmd == 'c') { //(x1,y1,x2,y2,x,y)
		for (size_t i = 0; i + 5 < nums.size(); i += 6) {
			command.data.push_back(Point2D(nums[i], nums[i + 1]));     
			command.data.push_back(Point2D(nums[i + 2], nums[i + 3])); 
			command.data.push_back(Point2D(nums[i + 4], nums[i + 5])); 
		}
	}
	else if (cmd == 'Z' || cmd == 'z') {}
	commands.push_back(command);
}

VOID SVGPath::processAttribute(char* attributeName, char* attributeValue) {
	if (strcmp(attributeName, "d") == 0) {
		string d(attributeValue);
		stringstream ss;
		char currCmd = '\0';
		float num;
		vector<float> nums;

		// M100,350 250,50
		for (size_t i = 0; i < d.size(); i++) {
			char c = d[i];
			if (isalpha(c)) { 
				if (currCmd != '\0') { 
					handleCommand(currCmd, nums);
					nums.clear();
				}
				currCmd = c;
			}
			else if (isdigit(c) || c == '-' || c == '.' || c == '+') { 
				ss.str("");
				ss.clear();
				ss << c;
				size_t j = i + 1;
				while (j < d.size() && (isdigit(d[j]) || d[j] == '.')) {
					ss << d[j];
					j++;
				}
				i = j - 1; 
				ss >> num;
				nums.push_back(num);
			}
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
			if (!cmd.data.empty()) {
				gp.StartFigure();
				current = PointF(cmd.data[0].getX(), cmd.data[0].getY());
			}
			break;
		case 'm':
			if (!cmd.data.empty()) {
				gp.StartFigure();
				current.X += cmd.data[0].getX();
				current.Y += cmd.data[0].getY();
			}
			break;
		case 'L':
			for (auto& point : cmd.data) {
				PointF newPoint(point.getX(), point.getY());
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'l':
			for (auto& point : cmd.data) {
				PointF newPoint(current.X + point.getX(), current.Y + point.getY());
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'H':
			for (auto& point : cmd.data) {
				PointF newPoint(point.getX(), current.Y);
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'h':
			for (auto& point : cmd.data) {
				PointF newPoint(current.X + point.getX(), current.Y);
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'V':
			for (auto& point : cmd.data) {
				PointF newPoint(current.X, point.getY());
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'v':
			for (auto& point : cmd.data) {
				PointF newPoint(current.X, current.Y + point.getY());
				gp.AddLine(current, newPoint);
				current = newPoint;
			}
			break;
		case 'C':
			for (size_t i = 0; i + 2 < cmd.data.size(); i += 3) {
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
				PointF c2(current.X + cmd.data[i + 1].getX(), current.Y + cmd.data[i + 1].getY());
				PointF endPoint(current.X + cmd.data[i + 2].getX(), current.Y + cmd.data[i + 2].getY());
				gp.AddBezier(current, c1, c2, endPoint);
				current = endPoint;
			}
			break;
		case 'Z':
		case 'z':
			gp.CloseFigure();
			break;
		}
	}

	SolidBrush brush(Color(fillOpacity,
		fill.getRed(),
		fill.getGreen(),
		fill.getBlue()));
	graphics.FillPath(&brush, &gp);

	Pen pen(Color(strokeOpacity,
		stroke.getRed(),
		stroke.getGreen(),
		stroke.getBlue()),
		strokeWidth);
	graphics.DrawPath(&pen, &gp);
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
	/*if (shape->getStrokeOpacity() == 0.0f && this->getStrokeOpacity() > 0.0f) {
		shape->setStroke(this->getStroke());
		shape->setStrokeOpacity(this->getStrokeOpacity());
	}
	if (shape->getStrokeWidth() == 0.0f && this->getStrokeWidth() > 0.0f) {
		shape->setStrokeWidth(this->getStrokeWidth());
	}
	if (shape->getFillOpacity() == 0.0f && this->getFillOpacity() > 0.0f) {
		shape->setFill(this->getFill());
		shape->setFillOpacity(this->getFillOpacity());
	}*/

	children.push_back(shape);
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
	//GraphicsState groupState = graphics.Save();

	// QUAN TRỌNG: Áp dụng SVG reader transforms trước
	//SVGShape::setGraphicsTransform(graphics);

	// Sau đó áp dụng group transforms
	//for (const auto& op : getTransform().getOperations()) {
	//	switch (op.type) {
	//	case TRANSLATE:
	//		graphics.TranslateTransform(op.values[0], op.values[1]);
	//		break;
	//	case ROTATE:
	//		// Xử lý rotation với center point chính xác
	//		if (op.valueCount >= 3) {
	//			graphics.TranslateTransform(op.values[1], op.values[2]);
	//			graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
	//			graphics.TranslateTransform(-op.values[1], -op.values[2]);
	//		}
	//		else {
	//			// Rotation around origin
	//			graphics.RotateTransform(op.values[0] * 180.0f / M_PI);
	//		}
	//		break;
	//	case SCALE:
	//		graphics.ScaleTransform(op.values[0], op.values[1]);
	//		break;
	//	}
	//}

	// Draw all child shapes
	GraphicsState groupState = graphics.Save();
	for (SVGShape* shape : children) {
		if (shape) {

			shape->setGraphicsTransform(graphics);

			shape->draw(graphics);


			graphics.Restore(groupState);
		}
	}
}