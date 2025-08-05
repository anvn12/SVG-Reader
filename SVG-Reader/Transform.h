#ifndef Transform_h
#define Transform_h
#pragma once

#include <vector>
#include <string>
#include <gdiplus.h>
using namespace std;


// declaration
class TransformAttribute;
class TransformTranslate;
class TransformScale;
class TransformRotate;


class Transform {
private:
    //float translateX, translateY;
    //float scaleX, scaleY;
    //float rotateAngle;

    std::vector<TransformAttribute*> transformAttributeList;

    void parseParameters(const string& paramStr, vector<float>& values);

public:
    Transform()
        //: translateX(0.0f), translateY(0.0f),
        //scaleX(1.0f), scaleY(1.0f),
        //rotateAngle(0.0f)
    {
    }

    ~Transform() {
        if (transformAttributeList.size() > 0) {
            for (size_t i = 0; i < transformAttributeList.size(); i++) {
                delete transformAttributeList[i];
            }
        }
    }

    void parseTransform(const string& transformStr);

    void applyToGraphics(Graphics* g) const;
};

// base class to store translate, rotate, scale in transform svg
class TransformAttribute {
public:
    TransformAttribute() {}
    virtual ~TransformAttribute() {}

    virtual void applyToGraphics(Graphics* g) = 0;
};

class TransformTranslate : public TransformAttribute {
private:
    float translateX, translateY;
public:
    TransformTranslate()
        : translateX(0.0f), translateY(0.0f) 
    {}
    // constructor with x
    TransformTranslate(float x)
        : translateX(x), translateY(0.0f)
    {}
    // constructor with x y
    TransformTranslate(float x, float y)
        : translateX(x), translateY(y) 
    {}

    ~TransformTranslate() override {}

    void applyToGraphics(Graphics* g) override;
};

class TransformScale : public TransformAttribute {
private:
    float scaleX, scaleY;
public:
    TransformScale()
        : scaleX(1.0f), scaleY(1.0f)
    {
    }
    // constructor with x
    TransformScale(float x)
        : scaleX(x), scaleY(x)
    {
    }
    // constructor with x y
    TransformScale(float x, float y)
        : scaleX(x), scaleY(y)
    {
    }

    ~TransformScale() override {}

    void applyToGraphics(Graphics* g) override;
};

class TransformRotate : public TransformAttribute {
private:
    float rotateAngle;
public:
    TransformRotate()
        : rotateAngle(0.0f)
    {
    }
    // constructor with x
    TransformRotate(float x)
        : rotateAngle(x)
    {
    }

    ~TransformRotate() override {}

    void applyToGraphics(Graphics* g) override;
};

#endif
