#include "stdafx.h"
#include "General.h"

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
double Point2D::getX() const {
    return x;
}

double Point2D::getY() const {
    return y;
}

double Point2D::getCx() const {
    return cx;
}

double Point2D::getCy() const {
    return cy;
}

double Point2D::getX1() const {
    return x1;
}

double Point2D::getX2() const {
    return x2;
}

double Point2D::getY1() const {
    return y1;
}

double Point2D::getY2() const {
    return y2;
}

//Point 2d setter
void Point2D::setX(int value) {
    x = value;
}

void Point2D::setY(int value) {
    y = value;
}

void Point2D::setCx(int value) {
    cx = value;
}

void Point2D::setCy(int value) {
    cy = value;
}

void Point2D::setX1(int value) {
    x1 = value;
}

void Point2D::setX2(int value)
{
    x2 = value;
}

void Point2D::setY1(int value) {
    y2 = value;
}

void Point2D::setY2(int value) {
    y2 = value;
}
