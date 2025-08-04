
#ifndef Transform_h
#define Transform_h
#pragma once

// Dinh nghia pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <vector>
#include <string>
#include <gdiplus.h>
using namespace std;

enum TransformType {    //de dinh nghia cac hang so co ten. Kiêu nhu la khi goi TRANSLATE thì no tu hieu la tinh tien...
    TRANSLATE,
    ROTATE,
    SCALE
};

//struct TransformOperation {
//    TransformType type;
//    float values[3]; // 3 gia tri (x, y, scale)
//    int valueCount;
//
//    TransformOperation(TransformType t) : type(t), valueCount(0) {
//        values[0] = values[1] = values[2] = 0.0f;
//    }
//};

//class Transform {
//private:
//    vector<TransformOperation> operations;
//    void parseParameters(const string& paramStr, vector<float>& values);
//
//public:
//    Transform() {}
//
//    void parseTransform(const string& transformStr);
//    void applyTransform(float& x, float& y) const;
//    bool hasTransform() const { return !operations.empty(); }
//
//    size_t getOperationCount() const { return operations.size(); }
//};

class Transform {
private:
    float translateX = 0.0f;
    float translateY = 0.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float rotateAngle = 0.0f; // radians
    float rotateCX = 0.0f;
    float rotateCY = 0.0f;

    void parseParameters(const string& paramStr, vector<float>& values);

public:
    Transform() {}

    void parseTransform(const string& transformStr);

    // Apply transform to a single point
    void applyTransform(float& x, float& y) const;

    // Apply transform to Graphics object
    void applyToGraphics(Graphics* g) const {
        // Apply translate
        if (translateX != 0.0f || translateY != 0.0f) {
            g->TranslateTransform(translateX, translateY, MatrixOrderAppend);
        }

        // Apply rotate
        if (rotateAngle != 0.0f) {
            g->TranslateTransform(rotateCX, rotateCY, MatrixOrderAppend);
            g->RotateTransform(rotateAngle * 180.0f / static_cast<float>(M_PI), MatrixOrderAppend);
            g->TranslateTransform(-rotateCX, -rotateCY, MatrixOrderAppend);
        }

        // Apply scale
        if (scaleX != 1.0f || scaleY != 1.0f) {
            g->ScaleTransform(scaleX, scaleY, MatrixOrderAppend);
        }
    }

    // Reset transform after drawing
    void resetGraphics(Graphics* g) const {
        g->ResetTransform();
    }

    bool hasTransform() const {
        return translateX != 0.0f || translateY != 0.0f ||
            scaleX != 1.0f || scaleY != 1.0f || rotateAngle != 0.0f;
    }

    // Getter methods
    float getTranslateX() const { return translateX; }
    float getTranslateY() const { return translateY; }
    float getScaleX() const { return scaleX; }
    float getScaleY() const { return scaleY; }
    float getRotateAngle() const { return rotateAngle; }
    float getRotateCX() const { return rotateCX; }
    float getRotateCY() const { return rotateCY; }
};

#endif
