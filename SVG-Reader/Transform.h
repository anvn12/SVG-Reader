// Transform.h
#ifndef Transform_h
#define Transform_h
#pragma once

#include <vector>
#include <string>
using namespace std;

enum TransformType {
    TRANSLATE,
    ROTATE,
    SCALE
};

struct TransformOperation {
    TransformType type;
    float values[3]; // 3 gia tri (x, y, scale)
    int valueCount;

    TransformOperation(TransformType t) : type(t), valueCount(0) {
        values[0] = values[1] = values[2] = 0.0f;
    }
};

class Transform {
private:
    vector<TransformOperation> operations;

public:
    Transform() {}

    void parseTransform(const string& transformStr);
    void applyTransform(float& x, float& y) const;
    bool hasTransform() const { return !operations.empty(); }
};

#endif