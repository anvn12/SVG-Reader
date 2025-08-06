#ifndef General_h
#define General_h
#pragma once

#include <vector>
#include <sstream>


class Point2D {
private:
	float x, y;

public:
	Point2D()
		: x(0), y(0) {}

	Point2D(float coorX, float coorY)
		: x(coorX), y(coorY) {}

	~Point2D() {}

	float getX() const { return x; }
	float getY() const { return y; }
	
	void setX(float value) { x = value; }
	void setY(float value) { y = value; }
};


//help for reading poly points
vector<PointF> parsePoints(const string& pointsStr);

#endif
