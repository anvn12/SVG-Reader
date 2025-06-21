#ifndef General_h
#define General_h
#pragma once

#include <vector>
#include <sstream>

// RGB color
class RGBColor {
private:
	int red, green, blue;

	int clamp(int value) const;

public:
	RGBColor()
		: red(0), green(0), blue(0) {}

	RGBColor(int r, int g, int b)
		: red(clamp(r)), green(clamp(g)), blue(clamp(b)) {}

	RGBColor getColor();

	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);
};

class Point2D {
private:
	int x, y;

public:
	Point2D()
		: x(0), y(0) {}

	Point2D(int coorX, int coorY)
		: x(coorX), y(coorY) {}

	int getX() const;
	int getY() const;
	

	void setX(int value);
	void setY(int value);
	
};


//help for reading poly points
vector<PointF> parsePoints(const string& pointsStr);

#endif
