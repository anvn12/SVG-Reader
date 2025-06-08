#ifndef ProcessXML_h
#define ProcessXML_h
#pragma once

#include "rapidxml.hpp"
#include "Shape.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;

VOID processXML(Graphics& graphics, string filename);

//void shapeProcess(Rectangle, char*, const char*);

#endif
