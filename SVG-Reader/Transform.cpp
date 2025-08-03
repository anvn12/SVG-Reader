#include "stdafx.h"
#include "Transform.h"
#include <sstream>
#include <cmath>

// Dinh nghia pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//void Transform::parseTransform(const string& transformStr) {
//    operations.clear();
//
//    stringstream ss(transformStr);
//    string token;
//
//    while (ss >> token) {
//        if (token.find("translate") == 0) {
//            TransformOperation op(TRANSLATE);
//
//            // Tim dau ( va )
//            size_t start = token.find('(');
//            size_t end = token.find(')');
//
//            if (start != string::npos && end != string::npos) {
//                string params = token.substr(start + 1, end - start - 1);
//                stringstream paramStream(params);
//                string param;
//
//                if (getline(paramStream, param, ',')) {
//                    op.values[0] = stof(param);
//                    op.valueCount++;
//
//                    if (getline(paramStream, param)) {
//                        op.values[1] = stof(param);
//                        op.valueCount++;
//                    }
//                }
//            }
//            operations.push_back(op);
//        }
//        //else if (token.find("rotate") == 0) {
//        //    TransformOperation op(ROTATE);
//
//        //    size_t start = token.find('(');
//        //    size_t end = token.find(')');
//
//        //    if (start != string::npos && end != string::npos) {
//        //        string params = token.substr(start + 1, end - start - 1);
//        //        op.values[0] = stof(params) * M_PI / 180.0f; // chuyen sang rad
//        //        op.valueCount = 1;
//        //    }
//        //    operations.push_back(op);
//        //}
//        else if (token.find("rotate") == 0) {
//            TransformOperation op(ROTATE);
//
//            size_t start = token.find('(');
//            size_t end = token.find(')');
//
//            if (start != string::npos && end != string::npos) {
//                string params = token.substr(start + 1, end - start - 1);
//                stringstream paramStream(params);
//                string param;
//
//                if (getline(paramStream, param, ',')) {
//                    op.values[0] = stof(param) * M_PI / 180.0f; // angle
//                    op.valueCount++;
//
//                    if (getline(paramStream, param, ',')) {
//                        op.values[1] = stof(param); // cx
//                        op.valueCount++;
//
//                        if (getline(paramStream, param)) {
//                            op.values[2] = stof(param); // cy
//                            op.valueCount++;
//                        }
//                    }
//                }
//            }
//            operations.push_back(op);
//        }
//        else if (token.find("scale") == 0) {
//            TransformOperation op(SCALE);
//
//            size_t start = token.find('(');
//            size_t end = token.find(')');
//
//            if (start != string::npos && end != string::npos) {
//                string params = token.substr(start + 1, end - start - 1);
//                stringstream paramStream(params);
//                string param;
//
//                if (getline(paramStream, param, ',')) {
//                    op.values[0] = stof(param);
//                    op.valueCount++;
//
//                    if (getline(paramStream, param)) {
//                        op.values[1] = stof(param);
//                        op.valueCount++;
//                    }
//                    else {
//                        op.values[1] = op.values[0]; // scale dong deu
//                        op.valueCount = 2;
//                    }
//                }
//            }
//            operations.push_back(op);
//        }
//    }
//}

void Transform::parseTransform(const string& transformStr) {
    operations.clear();

    if (transformStr.empty()) return;

    string str = transformStr;
    // Loại bỏ khoảng trắng thừa
    str.erase(remove_if(str.begin(), str.end(), [](char c) {
        return c == '\n' || c == '\r' || c == '\t';
        }), str.end());

    size_t pos = 0;
    while (pos < str.length()) {
        // Tìm tên transform
        while (pos < str.length() && isspace(str[pos])) pos++;
        if (pos >= str.length()) break;

        // Tìm vị trí bắt đầu của transform function
        size_t nameStart = pos;
        while (pos < str.length() && str[pos] != '(') pos++;
        if (pos >= str.length()) break;

        string transformName = str.substr(nameStart, pos - nameStart);
        // Loại bỏ khoảng trắng
        transformName.erase(remove_if(transformName.begin(), transformName.end(), isspace), transformName.end());

        // Tìm dấu đóng ngoặc
        size_t openParen = pos;
        pos++; // bỏ qua dấu '('
        size_t closeParen = pos;
        int parenCount = 1;
        while (closeParen < str.length() && parenCount > 0) {
            if (str[closeParen] == '(') parenCount++;
            else if (str[closeParen] == ')') parenCount--;
            closeParen++;
        }
        if (parenCount > 0) break; // không tìm thấy dấu đóng ngoặc

        string params = str.substr(pos, closeParen - pos - 1);
        pos = closeParen;

        // Parse parameters
        vector<float> values;
        parseParameters(params, values);

        // Tạo transform operation
        if (transformName == "translate") {
            TransformOperation op(TRANSLATE);
            if (values.size() >= 1) {
                op.values[0] = values[0];
                op.valueCount++;
                if (values.size() >= 2) {
                    op.values[1] = values[1];
                    op.valueCount++;
                }
                else {
                    op.values[1] = 0.0f; // mặc định ty = 0
                    op.valueCount++;
                }
            }
            operations.push_back(op);
        }
        else if (transformName == "rotate") {
            TransformOperation op(ROTATE);
            if (values.size() >= 1) {
                op.values[0] = values[0] * M_PI / 180.0f; // chuyển sang radian
                op.valueCount++;
                if (values.size() >= 3) {
                    op.values[1] = values[1]; // cx
                    op.values[2] = values[2]; // cy
                    op.valueCount = 3;
                }
                else {
                    op.values[1] = 0.0f; // mặc định cx = 0
                    op.values[2] = 0.0f; // mặc định cy = 0
                    op.valueCount = 3;
                }
            }
            operations.push_back(op);
        }
        else if (transformName == "scale") {
            TransformOperation op(SCALE);
            if (values.size() >= 1) {
                op.values[0] = values[0];
                op.valueCount++;
                if (values.size() >= 2) {
                    op.values[1] = values[1];
                    op.valueCount++;
                }
                else {
                    op.values[1] = op.values[0]; // scale đồng đều
                    op.valueCount++;
                }
            }
            operations.push_back(op);
        }
    }
}

//void Transform::parseParameters(const string& paramStr, vector<float>& values) {
//    if (paramStr.empty()) return;
//
//    string str = paramStr;
//    size_t pos = 0;
//
//    while (pos < str.length()) {
//        // Bỏ qua khoảng trắng và dấu phay
//        while (pos < str.length() && (isspace(str[pos]) || str[pos] == ',')) pos++;
//        if (pos >= str.length()) break;
//
//        // Tìm số
//        size_t numStart = pos;
//        if (str[pos] == '-' || str[pos] == '+') pos++; // dấu âm/dương
//
//        bool hasDot = false;
//        while (pos < str.length() && (isdigit(str[pos]) || (str[pos] == '.' && !hasDot))) {
//            if (str[pos] == '.') hasDot = true;
//            pos++;
//        }
//
//        if (pos > numStart) {
//            string numStr = str.substr(numStart, pos - numStart);
//            try {
//                float value = stof(numStr);
//                values.push_back(value);
//            }
//            catch (...) {
//                // Ignore invalid numbers
//            }
//        }
//    }
//}

void Transform::parseParameters(const string& paramStr, vector<float>& values) {
    if (paramStr.empty()) return;

    try {
        string str = paramStr;
        size_t pos = 0;

        while (pos < str.length()) {
          
            while (pos < str.length() && (isspace(str[pos]) || str[pos] == ',')) pos++;
            if (pos >= str.length()) break;

            size_t numStart = pos;
            if (pos < str.length() && (str[pos] == '-' || str[pos] == '+')) pos++; // dấu âm/dương

            bool hasDot = false;
            while (pos < str.length() && (isdigit(str[pos]) || (str[pos] == '.' && !hasDot))) {
                if (str[pos] == '.') hasDot = true;
                pos++;
            }

            if (pos > numStart) {
                string numStr = str.substr(numStart, pos - numStart);
                try {
                    float value = stof(numStr);
                    values.push_back(value);
                }
                catch (const std::exception&) {
                
                    continue;
                }
            }
        }
    }
    catch (...) {
        // Handle parsing errors
        values.clear();
    }
}

void Transform::applyTransform(float& x, float& y) const {
    for (const auto& op : operations) {
        switch (op.type) {
        case TRANSLATE:
            x += op.values[0];
            y += op.values[1];
            break;

     /*   case ROTATE: {
            float angle = op.values[0];
            float newX = x * cos(angle) - y * sin(angle);
            float newY = x * sin(angle) + y * cos(angle);
            x = newX;
            y = newY;
            break;
        }*/
        case ROTATE: {
            float angle = op.values[0];
            float cx = (op.valueCount >= 2) ? op.values[1] : 0.0f;
            float cy = (op.valueCount >= 3) ? op.values[2] : 0.0f;

            // translate to origin
            float tx = x - cx;
            float ty = y - cy;

            float newX = tx * cos(angle) - ty * sin(angle);
            float newY = tx * sin(angle) + ty * cos(angle);

            // translate back
            x = newX + cx;
            y = newY + cy;
            break;
        }


        case SCALE:
            x *= op.values[0];
            y *= op.values[1];
            break;
        }
    }
}