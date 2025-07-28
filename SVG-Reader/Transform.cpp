#include "Transform.h"
#include <sstream>
#include <cmath>

// Dinh nghia pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Transform::parseTransform(const string& transformStr) {
    operations.clear();

    stringstream ss(transformStr);
    string token;

    while (ss >> token) {
        if (token.find("translate") == 0) {
            TransformOperation op(TRANSLATE);

            // Tim dau ( va )
            size_t start = token.find('(');
            size_t end = token.find(')');

            if (start != string::npos && end != string::npos) {
                string params = token.substr(start + 1, end - start - 1);
                stringstream paramStream(params);
                string param;

                if (getline(paramStream, param, ',')) {
                    op.values[0] = stof(param);
                    op.valueCount++;

                    if (getline(paramStream, param)) {
                        op.values[1] = stof(param);
                        op.valueCount++;
                    }
                }
            }
            operations.push_back(op);
        }
        else if (token.find("rotate") == 0) {
            TransformOperation op(ROTATE);

            size_t start = token.find('(');
            size_t end = token.find(')');

            if (start != string::npos && end != string::npos) {
                string params = token.substr(start + 1, end - start - 1);
                op.values[0] = stof(params) * M_PI / 180.0f; // chuyen sang rad
                op.valueCount = 1;
            }
            operations.push_back(op);
        }
        else if (token.find("scale") == 0) {
            TransformOperation op(SCALE);

            size_t start = token.find('(');
            size_t end = token.find(')');

            if (start != string::npos && end != string::npos) {
                string params = token.substr(start + 1, end - start - 1);
                stringstream paramStream(params);
                string param;

                if (getline(paramStream, param, ',')) {
                    op.values[0] = stof(param);
                    op.valueCount++;

                    if (getline(paramStream, param)) {
                        op.values[1] = stof(param);
                        op.valueCount++;
                    }
                    else {
                        op.values[1] = op.values[0]; // scale dong deu
                        op.valueCount = 2;
                    }
                }
            }
            operations.push_back(op);
        }
    }
}

void Transform::applyTransform(float& x, float& y) const {
    for (const auto& op : operations) {
        switch (op.type) {
        case TRANSLATE:
            x += op.values[0];
            y += op.values[1];
            break;

        case ROTATE: {
            float angle = op.values[0];
            float newX = x * cos(angle) - y * sin(angle);
            float newY = x * sin(angle) + y * cos(angle);
            x = newX;
            y = newY;
            break;
        }

        case SCALE:
            x *= op.values[0];
            y *= op.values[1];
            break;
        }
    }
}