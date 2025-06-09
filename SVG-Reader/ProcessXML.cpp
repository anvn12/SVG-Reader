#include "stdafx.h"
#include "ProcessXML.h"
#include "Shape.h"

VOID processXML(Graphics& graphics, string filename) {
	// Ref: http://rapidxml.sourceforge.net/manual.html
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
		// node name là kiểu rect, polygon, text...
		char* nodeName = node->name();

		// Shape process
		if (strcmp(nodeName, "rect") == 0) {
			SVGRectangle object;

			// đây là mấy cái chỗ đọc thuộc tính -> bỏ vô object
			// Set breakpoint here to view value
			xml_attribute<>* curAttribute = node->first_attribute();
			while (curAttribute != NULL) {
				char* attributeName = curAttribute->name();
				char* attributeValue = curAttribute->value();

				object.processAttribute(attributeName, attributeValue);

				curAttribute = curAttribute->next_attribute();
			}
			// vẽ object lên màn hình
			object.draw(graphics);
		}

		node = node->next_sibling();
	}
}

