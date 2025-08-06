#include "stdafx.h"
#include "RGBAColor.h"
//#include "SVGReader.h"

//RGB Color private
//clamp(value, low, high) force value to be in range [low, high]
int RGBAColor::clamp(int value) const    
{
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    return value;
}
float RGBAColor::clamp(float value) const
{
    if (value < 0) {
        return 0;
    }
    else if (value > 255) {
        return 255;
    }
    return value;
}

void RGBAColor::textToRGB(char* text) {
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


    //int r{ 0 }, g{ 0 }, b{0};

    string stext = text;

    if (stext.substr(0, 3) == "rgb") {
        stext.erase(0, 4);
        stringstream ss(stext);
        string temp;
        getline(ss, temp, ',');
        red = stoi(temp);
        getline(ss, temp, ',');
        green = stoi(temp);
        getline(ss, temp, ')');
        blue = stoi(temp);

        if (isColor == false) {
            alpha = 255;
            isColor = true;
        }
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
            *this = hexToRGB(stext);
        }
        // #RGB
        else if (stext.length() == 4) {
            *this = shorthandHexToRGB(stext);
        }

        if (isColor == false) {
            alpha = 255;
            isColor = true;
        }
    }
    else if (stext == "red") {
        red = 255;

        if (isColor == false) {
            alpha = 255;
            isColor = true;
        }
    }
    else if (stext == "green") {
        green = 255;

        if (isColor == false) {
            alpha = 255;
            isColor = true;
        }
    }
    else if (stext == "blue") {
        blue = 255;

        if (isColor == false) {
            alpha = 255;
            isColor = true;
        }
    }
    else if (stext == "none") {
        isColor = false;
    }
    
    //return RGBAColor(r, g, b);
}

RGBAColor hexToRGB(const string& hex) {
    int r = stoi(hex.substr(1, 2), nullptr, 16);
    int g = stoi(hex.substr(3, 2), nullptr, 16);
    int b = stoi(hex.substr(5, 2), nullptr, 16);

    return RGBAColor(r, g, b);
}

RGBAColor shorthandHexToRGB(const string& hex) {
    char red = hex[1], green = hex[2], blue = hex[3];

    int r = stoi(string(2, red), nullptr, 16);
    int g = stoi(string(2, green), nullptr, 16);
    int b = stoi(string(2, blue), nullptr, 16);

    return RGBAColor(r, g, b);
}




