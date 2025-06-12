#include "stdafx.h"
#include "ProcessXML.h"
#include "Shape.h"

void renderShapes(SVGShape* shape, xml_node<>* node, Graphics& graphics) {
	SVGText* textShape = dynamic_cast<SVGText*>(shape);
	if (textShape && node->value()) {
		textShape->setContent(node->value());
	}

	xml_attribute<>* curAttribute = node->first_attribute();
	while (curAttribute != NULL) {
		char* attributeName = curAttribute->name();
		char* attributeValue = curAttribute->value();

		shape->processAttribute(attributeName, attributeValue);

		curAttribute = curAttribute->next_attribute();
	}

	shape->draw(graphics);
}

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
        char* nodeName = node->name();
        SVGShape* shape = nullptr;

        // Create shape based on type
        if (strcmp(nodeName, "rect") == 0) {
            shape = new SVGRectangle();
        }
        else if (strcmp(nodeName, "ellipse") == 0) {
            shape = new SVGEllipse();
        }
        else if (strcmp(nodeName, "circle") == 0) {
            shape = new SVGCircle();
        }
        else if (strcmp(nodeName, "text") == 0) {
            shape = new SVGText();
        }
        else if (strcmp(nodeName, "line") == 0) {
            shape = new SVGLine();
        }
        else if (strcmp(nodeName, "polyline") == 0) {
            shape = new SVGPolyline();
        }
        else if (strcmp(nodeName, "polygon") == 0) {
            shape = new SVGPolygon();
        }

        if (shape) {
            renderShapes(shape, node, graphics);
            delete shape; // Don't forget to clean up!
        }

        node = node->next_sibling();
    }
}

//VOID processXML(Graphics& graphics, string filename) {
//	// Ref: http://rapidxml.sourceforge.net/manual.html
//	// Read XML
//	xml_document<> doc;
//	xml_node<>* rootNode;
//	// Read the xml file into a vector
//	ifstream file(filename);
//	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//	buffer.push_back('\0');
//	// Parse the buffer using the xml file parsing library into doc 
//	doc.parse<0>(&buffer[0]);
//
//	rootNode = doc.first_node();
//	xml_node<>* node = rootNode->first_node();
//
//	while (node != NULL) {
//		// node name là kiểu rect, polygon, text...
//		char* nodeName = node->name();
//
//		// Shape process
//		if (strcmp(nodeName, "rect") == 0) {
//			SVGRectangle object;
//
//			// đây là mấy cái chỗ đọc thuộc tính -> bỏ vô object
//			// Set breakpoint here to view value
//			xml_attribute<>* curAttribute = node->first_attribute();
//			while (curAttribute != NULL) {
//				char* attributeName = curAttribute->name();
//				char* attributeValue = curAttribute->value();
//
//				object.processAttribute(attributeName, attributeValue);
//
//				curAttribute = curAttribute->next_attribute();
//			}
//			// vẽ object lên màn hình
//			object.draw(graphics);
//			
//		}
//		else if (strcmp(nodeName, "ellipse") == 0) {
//			SVGEllipse object;
//			xml_attribute<>* curAttribute = node->first_attribute();
//			while (curAttribute != NULL) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		else if (strcmp(nodeName, "circle") == 0) {
//			SVGCircle object;
//			xml_attribute<>* curAttribute = node->first_attribute();
//			while (curAttribute != NULL) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		else if (strcmp(nodeName, "text") == 0) {
//			SVGText object;
//
//			object.setContent(node->value());
//
//			xml_attribute<>* curAttribute = node->first_attribute();
//
//			while (curAttribute) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		else if (strcmp(nodeName, "line") == 0) {
//			SVGLine object;
//			xml_attribute<>* curAttribute = node->first_attribute();
//
//			while (curAttribute) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		else if (strcmp(nodeName, "polyline") == 0) {
//			SVGPolyline object;
//			xml_attribute<>* curAttribute = node->first_attribute();
//			
//			while (curAttribute) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		else if (strcmp(nodeName, "polygon") == 0) {
//			SVGPolygon object;
//			xml_attribute<>* curAttribute = node->first_attribute();
//
//			while (curAttribute) {
//				object.processAttribute(curAttribute->name(), curAttribute->value());
//				curAttribute = curAttribute->next_attribute();
//			}
//			object.draw(graphics);
//		}
//		node = node->next_sibling();
//	}
//}

