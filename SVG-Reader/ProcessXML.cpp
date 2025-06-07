#include "stdafx.h"
#include "ProcessXML.h"

void processXML(string filename)
{
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


		xml_attribute<>* curAttribute = node->first_attribute();
		while (curAttribute != NULL) {
			char* attributeName = curAttribute->name();
			char* attributeValue = curAttribute->value();


			// tạo mấy cái class rồi nhét vô



			curAttribute = curAttribute->next_attribute();
		}

		/*xml_attribute<>* firstAttribute = node->first_attribute();
		char* attributeName = firstAttribute->name();
		char* attributeValue = firstAttribute->value();
		xml_attribute<>* secondAttribute = firstAttribute->next_attribute();*/

		// Set breakpoint here to view value
		// Ref: http://rapidxml.sourceforge.net/manual.html
		node = node->next_sibling();


		// đây là mấy cái chỗ đọc thuộc tính, node name là kiểu rect...
		// bấm debug từ từ để coi giá trị
		// tạo mấy cái class rồi nhét vô
		// ========================
	}
}

