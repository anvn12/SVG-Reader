#include "stdafx.h"

int main()
{
	xml_document<> doc;
	std::ifstream file("sample.svg");

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	return 0;
}