#include "stdafx.h"
#include "Transform.h"
//#include <sstream>
//#include <cmath>


void Transform::parseTransform(const string& transformStr) {
    //// Reset to default values
    //translateX = 0.0f;
    //translateY = 0.0f;
    //scaleX = 1.0f;
    //scaleY = 1.0f;
    //rotateAngle = 0.0f;

    if (transformStr.empty()) return;

    std::string str = transformStr;
    // Remove whitespace
    str.erase(remove_if(str.begin(), str.end(), [](char c) {
        return c == '\n' || c == '\r' || c == '\t';
        }), str.end());

    size_t pos = 0;
    while (pos < str.length()) {
        // Find transform name
        while (pos < str.length() && isspace(str[pos])) pos++;
        if (pos >= str.length()) break;

        size_t nameStart = pos;
        while (pos < str.length() && str[pos] != '(') pos++;
        if (pos >= str.length()) break;

        string transformName = str.substr(nameStart, pos - nameStart);
        transformName.erase(remove_if(transformName.begin(), transformName.end(), isspace), transformName.end());

        // Find closing parenthesis
        size_t openParen = pos;
        pos++; // skip '('
        size_t closeParen = pos;
        int parenCount = 1;
        while (closeParen < str.length() && parenCount > 0) {
            if (str[closeParen] == '(') parenCount++;
            else if (str[closeParen] == ')') parenCount--;
            closeParen++;
        }
        if (parenCount > 0) break; // missing closing parenthesis

        string params = str.substr(pos, closeParen - pos - 1);
        pos = closeParen;

        // Parse parameters
        vector<float> values;
        parseParameters(params, values);

        // new attribute to be added to transform attribute list
        TransformAttribute* newAttribute = NULL;

        // Handle transforms
        if (transformName == "translate") {
            if (values.size() >= 1) {
                //translateX = values[0];
                //translateY = values.size() >= 2 ? values[1] : 0.0f;
                
                if (values.size() == 1) {
                    newAttribute = new TransformTranslate(values[0]);
                }
                else {
                    newAttribute = new TransformTranslate(values[0], values[1]);
                }
            }
        }
        else if (transformName == "scale") {
            if (values.size() >= 1) {
                //scaleX = values[0];
                //scaleY = values.size() >= 2 ? values[1] : scaleX;

                if (values.size() == 1) {
                    newAttribute = new TransformScale(values[0]);
                }
                else {
                    newAttribute = new TransformScale(values[0], values[1]);
                }
            }
        }
        else if (transformName == "rotate") {
            if (values.size() >= 1) {
                //rotateAngle = values[0]; // Store as degrees

                newAttribute = new TransformRotate(values[0]);
            }
        }

        if (newAttribute != NULL) {
            transformAttributeList.push_back(newAttribute);
        }
    }
}

void Transform::parseParameters(const std::string& paramStr, vector<float>& values) {
    if (paramStr.empty()) return;

    try {
        std::string str = paramStr;
        size_t pos = 0;

        while (pos < str.length()) {
            while (pos < str.length() && (isspace(str[pos]) || str[pos] == ',')) pos++;
            if (pos >= str.length()) break;

            size_t numStart = pos;
            if (pos < str.length() && (str[pos] == '-' || str[pos] == '+')) pos++;

            bool hasDot = false;
            while (pos < str.length() && (isdigit(str[pos]) || (str[pos] == '.' && !hasDot))) {
                if (str[pos] == '.') hasDot = true;
                pos++;
            }

            if (pos > numStart) {
                std::string numStr = str.substr(numStart, pos - numStart);
                try {
                    float value = stof(numStr);
                    values.push_back(value);
                }
                catch (const exception&) {
                    continue;
                }
            }
        }
    }
    catch (...) {
        values.clear();
    }
}

void Transform::applyToGraphics(Gdiplus::Graphics* g) const {
    for (size_t i = 0; i < transformAttributeList.size(); i++) {
        transformAttributeList[i]->applyToGraphics(g);
    }



    //// Apply transforms in correct order: Scale -> Rotate -> Translate
    //// Scale
    //if (scaleX != 1.0f || scaleY != 1.0f) {
    //    g->ScaleTransform(scaleX, scaleY, Gdiplus::MatrixOrderAppend);
    //}

    //// Rotate
    //if (rotateAngle != 0.0f) {
    //    g->RotateTransform(rotateAngle, Gdiplus::MatrixOrderAppend);
    //}

    //// Translate
    //if (translateX != 0.0f || translateY != 0.0f) {
    //    g->TranslateTransform(translateX, translateY, Gdiplus::MatrixOrderAppend);
    //}
}


void TransformTranslate::applyToGraphics(Graphics* g) {
    // Translate
    if (translateX != 0.0f || translateY != 0.0f) {
        g->TranslateTransform(translateX, translateY, Gdiplus::MatrixOrderAppend);
    }
}

void TransformScale::applyToGraphics(Graphics* g) {
    // Scale
    if (scaleX != 1.0f || scaleY != 1.0f) {
        g->ScaleTransform(scaleX, scaleY, Gdiplus::MatrixOrderAppend);
    }
}

void TransformRotate::applyToGraphics(Graphics* g) {
    // Rotate
    if (rotateAngle != 0.0f) {
        g->RotateTransform(rotateAngle, Gdiplus::MatrixOrderAppend);
    }
}