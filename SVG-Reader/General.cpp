#include "stdafx.h"
#include "General.h"
#include "SVGReader.h"





vector<Gdiplus::PointF> parsePoints(const string& pointsStr) {
    vector<Gdiplus::PointF> points;
    if (pointsStr.empty()) return points;

    istringstream iss(pointsStr);
    vector<float> nums;
    float v;

    while (iss >> v) {
        nums.push_back(v);
        //eats any ',' between "x,y"
        while (iss.peek() == ',') iss.get();
        //operator >> eats ' '
    }

    // Pair up numbers into (x,y)
    for (size_t i = 0; i + 1 < nums.size(); i += 2) {
        points.emplace_back(nums[i], nums[i + 1]);
    }

    return points;
}



