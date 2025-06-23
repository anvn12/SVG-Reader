#include "stdafx.h"
#include "General.h"
#include "SVGReader.h"

//RGB Color private
int RGBColor::clamp(int value) const    //clamp(value, low, high) -> nho hon low: tra ve low, lon hon high: tra ve high
{
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    return value;
}

//RGB Color
RGBColor RGBColor::getColor() {
    return *this;
}

int RGBColor::getRed() const {
    return red;
}

int RGBColor::getGreen() const {
    return green;
}

int RGBColor::getBlue() const {
    return blue;
}

void RGBColor::setRed(int r) {
    red = clamp(r);
}

void RGBColor::setGreen(int g) {
    green = clamp(g);
}

void RGBColor::setBlue(int b) {
    blue = clamp(b);
}


//Point 2d getter
int Point2D::getX() const {
    return x;
}

int Point2D::getY() const {
    return y;
}



//Point 2d setter
void Point2D::setX(int value) {
    x = value;
}

void Point2D::setY(int value) {
    y = value;
}


//vector<PointF> parsePoints(const string& pointsStr) {
//    vector<PointF> points;
//    stringstream ss(pointsStr);
//    string token;
//
//    while (getline(ss, token, ' ')) {
//        if (token.empty()) continue;
//
//        size_t commaPos = token.find(',');
//        if (commaPos != string::npos) {
//            float x = stof(token.substr(0, commaPos));
//            float y = stof(token.substr(commaPos + 1));
//            points.push_back(PointF(x, y));
//        }
//    }
//    return points;
//}

//vector<PointF> parsePoints(const string& pointsStr) {
vector<PointF> parsePoints(string pointsStr) {
    vector<PointF> points;
    istringstream iss(pointsStr);
    if (pointsStr.empty()) return points;

    char ch;
    float x, y;

    const SVGReader& reader = SVGReader::getInstance();
    float offsetX = reader.getX(); 
    float offsetY = reader.getY();
    float scale = reader.getScale();

    while (iss >> x >> ch >> y) {
        points.emplace_back(
            x * scale + offsetX,
            y * scale + offsetY
        );
        while (iss.peek() == ' ' || iss.peek() == ',') iss.ignore();
    }
    return points;
}