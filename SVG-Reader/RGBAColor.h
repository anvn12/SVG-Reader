#ifndef RGBAColor_h
#define RGBAColor_h
#pragma once


#include <vector>
#include <sstream>

using namespace std;

// RGBA color
class RGBAColor {
private:
	int red, green, blue;

	float alpha;

	bool isColor;

	int clamp(int value) const;
	float clamp(float value) const;

public:
	RGBAColor()
		: red(0), green(0), blue(0), alpha(255), isColor(false) {}

	RGBAColor(int r, int g, int b)
		: red(clamp(r)), green(clamp(g)), blue(clamp(b)), alpha(255), isColor(true) {}
	
	RGBAColor(int r, int g, int b, float a)
		: red(clamp(r)), green(clamp(g)), blue(clamp(b)), alpha(clamp(a)), isColor(true) {
	}

	~RGBAColor() {}

	RGBAColor getColor() { return *this; }

	int getRed() const { return red; }
	int getGreen() const { return green; }
	int getBlue() const { return blue; }
	float getAlpha() const { return alpha; }

	bool getIsColor() const { return isColor; }

	void setRed(int r) { red = clamp(r); }
	void setGreen(int g) { green = clamp(g); }
	void setBlue(int b) { blue = clamp(b); }
	float setAlpha(float a) { alpha = a; }

	// extract char* to RGBColor
	void textToRGB(char*);
};

RGBAColor hexToRGB(const string& hex);

RGBAColor shorthandHexToRGB(const string& hex);

#endif
