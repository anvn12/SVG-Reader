#include "stdafx.h"
#include "General.h"
#include "SVGReader.h"

//RGB Color private
//clamp(value, low, high) force value to be in range [low, high]
int RGBColor::clamp(int value) const    
{
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    return value;
}


RGBColor textToRGB(char* text) {
    // rgb(200,200,200)
    // c-style string to string
    string stext = text;
    int r, g, b;
    stext.erase(0, 4);
    stringstream ss(stext);
    string temp;
    getline(ss, temp, ',');
    r = stoi(temp);
    getline(ss, temp, ',');
    g = stoi(temp);
    getline(ss, temp, ')');
    b = stoi(temp);

    return RGBColor(r, g, b);
}


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



