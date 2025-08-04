
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
    float translateX, translateY;
    float scaleX, scaleY;
    float rotateAngle;

    void parseParameters(const string& paramStr, vector<float>& values);

public:
    Transform()
        : translateX(0.0f), translateY(0.0f),
        scaleX(1.0f), scaleY(1.0f),
        rotateAngle(0.0f)
    {
    }

    void parseTransform(const string& transformStr);

    void applyToGraphics(Graphics* g) const;

};

#endif
