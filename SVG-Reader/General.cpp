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
    // These are color formats in SVG:
    //Named color	"red"
    //Hexadecimal	"#ff0000" / "#f00"
    //RGB	"rgb(255,0,0)"
    //RGBA	"rgba(255,0,0,0.5)"
    //HSL	"hsl(0,100%,50%)"
    //HSLA	"hsla(0,100%,50%,0.5)"
    //currentColor	"currentColor"
    // 
    // 
    // c-style string to string
    //fill = "none"


    int r{ 0 }, g{ 0 }, b{0};

    string stext = text;

    if (stext.substr(0, 3) == "rgb") {
        stext.erase(0, 4);
        stringstream ss(stext);
        string temp;
        getline(ss, temp, ',');
        r = stoi(temp);
        getline(ss, temp, ',');
        g = stoi(temp);
        getline(ss, temp, ')');
        b = stoi(temp);
    }
    //else if (stext.substr(0, 4) == "rgba") {
    //
    //}
    //else if (stext.substr(0, 3) == "hsl") {
    //    //stext.erase(0, 4);
    //    //stringstream ss(stext);
    //    //string temp;
    //    //getline(ss, temp, ',');
    //    //r = stoi(temp);
    //    //getline(ss, temp, ',');
    //    //g = stoi(temp);
    //    //getline(ss, temp, ')');
    //    //b = stoi(temp);
    //}
    //else if (stext.substr(0, 4) == "hsla") {
    //
    //}
    else if (stext[0] == '#') {
        // #RRGGBB
        if (stext.length() == 7) {
            return hexToRGB(stext);
        }
        // #RGB
        else if (stext.length() == 4) {
            return shorthandHexToRGB(stext);
        }
    }
    else if (stext == "red") {
        r = 255;
    }
    else if (stext == "green") {
        g = 255;
    }
    else if (stext == "blue") {
        b = 255;
    }
    else if (stext == "none") {

    }
    

    return RGBColor(r, g, b);
}

RGBColor hexToRGB(const string& hex) {
    int r = stoi(hex.substr(1, 2), nullptr, 16);
    int g = stoi(hex.substr(3, 2), nullptr, 16);
    int b = stoi(hex.substr(5, 2), nullptr, 16);

    return RGBColor(r, g, b);
}

RGBColor shorthandHexToRGB(const string& hex) {
    char red = hex[1], green = hex[2], blue = hex[3];

    int r = stoi(string(2, red), nullptr, 16);
    int g = stoi(string(2, green), nullptr, 16);
    int b = stoi(string(2, blue), nullptr, 16);

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



