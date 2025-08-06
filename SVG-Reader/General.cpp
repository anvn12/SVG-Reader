#include "stdafx.h"
#include "General.h"
#include "SVGReader.h"





vector<Gdiplus::PointF> parsePoints(const string& pointsStr) {
    vector<Gdiplus::PointF> points;
    istringstream iss(pointsStr);
    if (pointsStr.empty()) return points;

    char ch;
    float x, y;

    while (iss >> x >> ch >> y) {
        points.emplace_back(x, y);
        while (iss.peek() == ' ' || iss.peek() == ',') iss.ignore();
    }
    return points;
}



