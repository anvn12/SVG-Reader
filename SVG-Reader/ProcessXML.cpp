#include "stdafx.h"
#include "ProcessXML.h"
#include "Shape.h"

VOID processXML(Graphics& graphics, string filename) {
	// Read XML
	xml_document<> doc;
	xml_node<>* rootNode;
	// Read the xml file into a vector
	ifstream file(filename);
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);

	rootNode = doc.first_node();
	xml_node<>* node = rootNode->first_node();

	while (node != NULL) {
		char* nodeName = node->name();

		// Shape process
		if (strcmp(nodeName, "rect") == 0) {
			SVGRectangle object;

			xml_attribute<>* curAttribute = node->first_attribute();
			while (curAttribute != NULL) {
				char* attributeName = curAttribute->name();
				char* attributeValue = curAttribute->value();

				// ===========
				object.processAttribute(attributeName, attributeValue);


				curAttribute = curAttribute->next_attribute();
			}

			// xong hết attribute thì vẽ ở đây

		}
	

		// Set breakpoint here to view value
		// Ref: http://rapidxml.sourceforge.net/manual.html
		node = node->next_sibling();


		// đây là mấy cái chỗ đọc thuộc tính, node name là kiểu rect...
		// bấm debug từ từ để coi giá trị

		// ========================

		Pen      pen(Color(255, 0, 0, 255));		// argb (alpha = opacity 0 -> 255, red, green, blue)

		//graphics.DrawLine(&pen, 0, 0, 200, 100);

		SolidBrush solidBrush(Color(255, 255, 0, 0));

		Rect ball1 = Rect(5, 5, 100, 100);
		Rect ball2 = Rect(105, 5, 100, 100);
		Rect body = Rect(55, 105, 100, 300);

		graphics.DrawEllipse(&pen, Rect(5, 5, 100, 100));
		graphics.FillEllipse(&solidBrush, ball1);

		graphics.DrawEllipse(&pen, ball2);
		graphics.FillEllipse(&solidBrush, ball2);

		graphics.DrawRectangle(&pen, body);
		graphics.FillRectangle(&solidBrush, body);
	}
}

//VOID processAttribute(Rectangle& object, char* attributeName, char* attributeValue) {
//	if (attributeName == "fill-opacity") {
//		object.fillOpacity = atoi(attributeValue);
//	}
//	else if (attributeName == "x") {
//		object.position.x = atoi(attributeValue);
//	}
//	else if (attributeName == "y") {
//		object.position.y = atoi(attributeValue);
//	}
//
//}
