//
//  ofxFunctionalEasingFunctions.h
//
//  Created by ISHII 2bit on 2015/09/21.
//
//

#pragma once

using EasingFunction = std::function<void(float progress)>;

namespace ofxFunctional {
    using TemplateFunction = float(*)(float progress, float start_value, float end_value);
#   define DefEase(name, body) inline float name(float p, float s, float e) { return body; }
#   define d (e - s)
    DefEase(Linear,  p * d + s);
    
    DefEase(InQuad,    d * p * p + s);
    DefEase(OutQuad,   -d * p * (p - 2.0f) + s);
    DefEase(InOutQuad, ((p *= 2.0f) < 1.0f) ? InQuad(p, s, 0.5f * (e + s)) : 0.5f * d * ((p - 1.0f) * (p - 3.0f) - 1.0f) + s);
    
    DefEase(InQubic,    d * p * p * p + s);
    DefEase(OutQubic,   d * ((p - 1.0f) * (p - 1.0f) * (p - 1.0f) + 1) + s);
    DefEase(InOutQubic, ((p *= 2.0f) < 1.0f) ? InQubic(p, s, 0.5f * (e + s)) : 0.5f * d * ((p - 2.0f) * (p - 2.0f) * (p - 2.0f) + 2.0f) + s);
};

#include <functional>
#include <type_traits>

template <typename T, typename std::enable_if<is_arithmetic<T>::value>::type *_=nullptr>
EasingFunction EasingFromTemplate(ofxFunctional::TemplateFunction f, T &binded_value, T start_value, T end_value) {
    return [=,&binded_value](float progress) {
        binded_value = f(progress, start_value, end_value);
    };
}