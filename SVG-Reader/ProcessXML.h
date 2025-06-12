#ifndef ProcessXML_h
#define ProcessXML_h
#pragma once

#include "rapidxml.hpp"
#include "Shape.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;

void renderShapes(SVGShape* shape, xml_node<>* node, Graphics& graphics);
VOID processXML(Graphics& graphics, string filename);

#endif
