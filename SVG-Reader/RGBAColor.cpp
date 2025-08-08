#include "stdafx.h"
#include "RGBAColor.h"
#include <map>
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

void RGBAColor::textToRGBA(char* text) {
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

    static const map<string, RGBAColor> namedColors = {
        {"aliceblue", RGBAColor(240, 248, 255)},
        {"antiquewhite", RGBAColor(250, 235, 215)},
        {"aqua", RGBAColor(0, 255, 255)},
        {"aquamarine", RGBAColor(127, 255, 212)},
        {"azure", RGBAColor(240, 255, 255)},
        {"beige", RGBAColor(245, 245, 220)},
        {"bisque", RGBAColor(255, 228, 196)},
        {"black", RGBAColor(0, 0, 0)},
        {"blanchedalmond", RGBAColor(255, 235, 205)},
        {"blue", RGBAColor(0, 0, 255)},
        {"blueviolet", RGBAColor(138, 43, 226)},
        {"brown", RGBAColor(165, 42, 42)},
        {"burlywood", RGBAColor(222, 184, 135)},
        {"cadetblue", RGBAColor(95, 158, 160)},
        {"chartreuse", RGBAColor(127, 255, 0)},
        {"chocolate", RGBAColor(210, 105, 30)},
        {"coral", RGBAColor(255, 127, 80)},
        {"cornflowerblue", RGBAColor(100, 149, 237)},
        {"cornsilk", RGBAColor(255, 248, 220)},
        {"crimson", RGBAColor(220, 20, 60)},
        {"cyan", RGBAColor(0, 255, 255)},
        {"darkblue", RGBAColor(0, 0, 139)},
        {"darkcyan", RGBAColor(0, 139, 139)},
        {"darkgoldenrod", RGBAColor(184, 134, 11)},
        {"darkgray", RGBAColor(169, 169, 169)},
        {"darkgreen", RGBAColor(0, 100, 0)},
        {"darkgrey", RGBAColor(169, 169, 169)},
        {"darkkhaki", RGBAColor(189, 183, 107)},
        {"darkmagenta", RGBAColor(139, 0, 139)},
        {"darkolivegreen", RGBAColor(85, 107, 47)},
        {"darkorange", RGBAColor(255, 140, 0)},
        {"darkorchid", RGBAColor(153, 50, 204)},
        {"darkred", RGBAColor(139, 0, 0)},
        {"darksalmon", RGBAColor(233, 150, 122)},
        {"darkseagreen", RGBAColor(143, 188, 143)},
        {"darkslateblue", RGBAColor(72, 61, 139)},
        {"darkslategray", RGBAColor(47, 79, 79)},
        {"darkslategrey", RGBAColor(47, 79, 79)},
        {"darkturquoise", RGBAColor(0, 206, 209)},
        {"darkviolet", RGBAColor(148, 0, 211)},
        {"deeppink", RGBAColor(255, 20, 147)},
        {"deepskyblue", RGBAColor(0, 191, 255)},
        {"dimgray", RGBAColor(105, 105, 105)},
        {"dimgrey", RGBAColor(105, 105, 105)},
        {"dodgerblue", RGBAColor(30, 144, 255)},
        {"firebrick", RGBAColor(178, 34, 34)},
        {"floralwhite", RGBAColor(255, 250, 240)},
        {"forestgreen", RGBAColor(34, 139, 34)},
        {"fuchsia", RGBAColor(255, 0, 255)},
        {"gainsboro", RGBAColor(220, 220, 220)},
        {"ghostwhite", RGBAColor(248, 248, 255)},
        {"gold", RGBAColor(255, 215, 0)},
        {"goldenrod", RGBAColor(218, 165, 32)},
        {"gray", RGBAColor(128, 128, 128)},
        {"green", RGBAColor(0, 128, 0)},
        {"greenyellow", RGBAColor(173, 255, 47)},
        {"grey", RGBAColor(128, 128, 128)},
        {"honeydew", RGBAColor(240, 255, 240)},
        {"hotpink", RGBAColor(255, 105, 180)},
        {"indianred", RGBAColor(205, 92, 92)},
        {"indigo", RGBAColor(75, 0, 130)},
        {"ivory", RGBAColor(255, 255, 240)},
        {"khaki", RGBAColor(240, 230, 140)},
        {"lavender", RGBAColor(230, 230, 250)},
        {"lavenderblush", RGBAColor(255, 240, 245)},
        {"lawngreen", RGBAColor(124, 252, 0)},
        {"lemonchiffon", RGBAColor(255, 250, 205)},
        {"lightblue", RGBAColor(173, 216, 230)},
        {"lightcoral", RGBAColor(240, 128, 128)},
        {"lightcyan", RGBAColor(224, 255, 255)},
        {"lightgoldenrodyellow", RGBAColor(250, 250, 210)},
        {"lightgray", RGBAColor(211, 211, 211)},
        {"lightgreen", RGBAColor(144, 238, 144)},
        {"lightgrey", RGBAColor(211, 211, 211)},
        {"lightpink", RGBAColor(255, 182, 193)},
        {"lightsalmon", RGBAColor(255, 160, 122)},
        {"lightseagreen", RGBAColor(32, 178, 170)},
        {"lightskyblue", RGBAColor(135, 206, 250)},
        {"lightslategray", RGBAColor(119, 136, 153)},
        {"lightslategrey", RGBAColor(119, 136, 153)},
        {"lightsteelblue", RGBAColor(176, 196, 222)},
        {"lightyellow", RGBAColor(255, 255, 224)},
        {"lime", RGBAColor(0, 255, 0)},
        {"limegreen", RGBAColor(50, 205, 50)},
        {"linen", RGBAColor(250, 240, 230)},
        {"magenta", RGBAColor(255, 0, 255)},
        {"maroon", RGBAColor(128, 0, 0)},
        {"mediumaquamarine", RGBAColor(102, 205, 170)},
        {"mediumblue", RGBAColor(0, 0, 205)},
        {"mediumorchid", RGBAColor(186, 85, 211)},
        {"mediumpurple", RGBAColor(147, 112, 219)},
        {"mediumseagreen", RGBAColor(60, 179, 113)},
        {"mediumslateblue", RGBAColor(123, 104, 238)},
        {"mediumspringgreen", RGBAColor(0, 250, 154)},
        {"mediumturquoise", RGBAColor(72, 209, 204)},
        {"mediumvioletred", RGBAColor(199, 21, 133)},
        {"midnightblue", RGBAColor(25, 25, 112)},
        {"mintcream", RGBAColor(245, 255, 250)},
        {"mistyrose", RGBAColor(255, 228, 225)},
        {"moccasin", RGBAColor(255, 228, 181)},
        {"navajowhite", RGBAColor(255, 222, 173)},
        {"navy", RGBAColor(0, 0, 128)},
        {"oldlace", RGBAColor(253, 245, 230)},
        {"olive", RGBAColor(128, 128, 0)},
        {"olivedrab", RGBAColor(107, 142, 35)},
        {"orange", RGBAColor(255, 165, 0)},
        {"orangered", RGBAColor(255, 69, 0)},
        {"orchid", RGBAColor(218, 112, 214)},
        {"palegoldenrod", RGBAColor(238, 232, 170)},
        {"palegreen", RGBAColor(152, 251, 152)},
        {"paleturquoise", RGBAColor(175, 238, 238)},
        {"palevioletred", RGBAColor(219, 112, 147)},
        {"papayawhip", RGBAColor(255, 239, 213)},
        {"peachpuff", RGBAColor(255, 218, 185)},
        {"peru", RGBAColor(205, 133, 63)},
        {"pink", RGBAColor(255, 192, 203)},
        {"plum", RGBAColor(221, 160, 221)},
        {"powderblue", RGBAColor(176, 224, 230)},
        {"purple", RGBAColor(128, 0, 128)},
        {"red", RGBAColor(255, 0, 0)},
        {"rosybrown", RGBAColor(188, 143, 143)},
        {"royalblue", RGBAColor(65, 105, 225)},
        {"saddlebrown", RGBAColor(139, 69, 19)},
        {"salmon", RGBAColor(250, 128, 114)},
        {"sandybrown", RGBAColor(244, 164, 96)},
        {"seagreen", RGBAColor(46, 139, 87)},
        {"seashell", RGBAColor(255, 245, 238)},
        {"sienna", RGBAColor(160, 82, 45)},
        {"silver", RGBAColor(192, 192, 192)},
        {"skyblue", RGBAColor(135, 206, 235)},
        {"slateblue", RGBAColor(106, 90, 205)},
        {"slategray", RGBAColor(112, 128, 144)},
        {"slategrey", RGBAColor(112, 128, 144)},
        {"snow", RGBAColor(255, 250, 250)},
        {"springgreen", RGBAColor(0, 255, 127)},
        {"steelblue", RGBAColor(70, 130, 180)},
        {"tan", RGBAColor(210, 180, 140)},
        {"teal", RGBAColor(0, 128, 128)},
        {"thistle", RGBAColor(216, 191, 216)},
        {"tomato", RGBAColor(255, 99, 71)},
        {"turquoise", RGBAColor(64, 224, 208)},
        {"violet", RGBAColor(238, 130, 238)},
        {"wheat", RGBAColor(245, 222, 179)},
        {"white", RGBAColor(255, 255, 255)},
        {"whitesmoke", RGBAColor(245, 245, 245)},
        {"yellow", RGBAColor(255, 255, 0)},
        {"yellowgreen", RGBAColor(154, 205, 50)}
    };


    //rgb tim rgba truoc de tranh trung1 voi rgb
    if (stext.rfind("rgba(", 0) == 0) {
        auto l = stext.find('('), r = stext.find(')'); //tim ngoac trai phai
        if (l != string::npos && r != string::npos && r > l) {
            string inside = stext.substr(l + 1, r - l - 1);
            stringstream ss(inside);
            string a, b, c, d;
            if (getline(ss, a, ',') && getline(ss, b, ',') &&
                getline(ss, c, ',') && getline(ss, d, ',')) {
                red = clamp(stoi(a));
                green = clamp(stoi(b));
                blue = clamp(stoi(c));
                // alpha is 0..1, scale to 0..255
                alpha = clamp(static_cast<float>(stof(d) * 255.0f));
                isColor = true;
                return;
            }
        }
    }

    //rgb
    if (stext.rfind("rgb(", 0) == 0) {
        auto l = stext.find('('), r = stext.find(')');
        if (l != string::npos && r != string::npos && r > l) {
            string inside = stext.substr(l + 1, r - l - 1);
            stringstream ss(inside);
            string a, b, c;
            if (getline(ss, a, ',') && getline(ss, b, ',') &&
                getline(ss, c, ',')) {
                red = clamp(stoi(a));
                green = clamp(stoi(b));
                blue = clamp(stoi(c));
                alpha = 255;
                isColor = true;
                return;
            }
        }
    }
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




