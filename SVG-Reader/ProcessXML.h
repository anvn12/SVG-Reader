#ifndef ProcessXML_h
#define ProcessXML_h
#pragma once

#include "rapidxml.hpp"
#include "Shape.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;

void processXML(string filename);

//void shapeProcess(Rectangle, char*, const char*);

#endif
