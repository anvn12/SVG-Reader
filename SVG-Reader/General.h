#ifndef General_h
#define General_h
#pragma once

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
	double x, y, cx, cy, x1, x2, y1, y2;

public:
	Point2D()
		: x(0), y(0), cx(0), cy(0), x1(0), x2(0), y1(0), y2(0) {}

	Point2D(double coorX, double coorY, double coorCx, double coorCy, double coorX1, double coorX2, double coorY1, double coorY2)
		: x(coorX), y(coorY), cx(coorCx), cy(coorCy), x1(coorX1), x2(coorX2), y1(coorY1), y2(coorY2) {}

	double getX() const;
	double getY() const;
	double getCx() const;
	double getCy() const;
	double getX1() const;
	double getX2() const;
	double getY1() const;
	double getY2() const;

	void setX(int value);
	void setY(int value);
	void setCx(int value);
	void setCy(int value);
	void setX1(int value);
	void setX2(int value);
	void setY1(int value);
	void setY2(int value);
};


#endif
