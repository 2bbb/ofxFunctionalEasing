//
//  ofxFunctionalEasing.h
//
//  Created by ISHII 2bit on 2015/09/21.
//
//

#pragma once

#include "ofMain.h"
#include <initializer_list>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "ofxFunctionalEasingFunctions.h"

using EasingCallback = std::function<void(const std::string &)>;

namespace ofxFunctional {
    static EasingCallback defaultCallback = [](const std::string &){};
    class Easing {
        class Manager {
            using EasingMap = std::unordered_map<std::string, std::shared_ptr<Easing>>;
            EasingMap easings;
            Manager() {
                ofAddListener(ofEvents().update, this, &Manager::update);
            }
        public:
            void update(ofEventArgs &) {
                const float currentTime = ofGetElapsedTimef();
                for(EasingMap::iterator it = easings.begin(); it != easings.end();) {
                    if(it->second->update(currentTime)) {
                        it->second->finish();
                        it = easings.erase(it);
                    } else {
                        it++;
                    }
                }
            }
            static Manager *getManager() {
                static Manager *manager = new Manager();
                return manager;
            }

            void push(std::shared_ptr<Easing> easing, const std::string &label) {
                easings.insert(std::make_pair(label, easing));
            }
        };
        
        vector<EasingFunction> easings;
        float duration, delay;
        std::string label;
        std::function<void(const std::string &)> callback;
        float startTime, endTime;
        
        Easing(std::vector<EasingFunction> easings,
               float duration,
               float delay,
               const std::string &label,
               EasingCallback callback)
        : duration(duration)
        , delay(delay)
        , callback(callback)
        , label(label)
        {
            this->easings.swap(easings);
            startTime = delay + ofGetElapsedTimef();
            endTime = startTime + duration;
        }
        
        Easing(std::initializer_list<EasingFunction> easings,
               float duration,
               float delay,
               const std::string &label,
               EasingCallback callback)
        : easings(easings)
        , duration(duration)
        , delay(delay)
        , callback(callback)
        , label(label)
        {
            startTime = delay + ofGetElapsedTimef();
            endTime = startTime + duration;
        }
    public:
        static void factory(std::vector<EasingFunction> easings,
                            float duration,
                            float delay,
                            const std::string &label,
                            EasingCallback callback)
        {
            Manager::getManager()->push(std::shared_ptr<Easing>(new Easing(easings, duration, delay, label, callback)), label);
        }
        
        bool update(float time) {
            if(time < startTime) return false;
            float progress = ofMap(time, startTime, endTime, 0.0f, 1.0f, true);
            for(auto &easing : easings) easing(progress);
            return 1.0f <= progress;
        }
        
        void finish() {
            callback(label);
        }
    };
};

std::string ofxFunctionalEasing(std::vector<EasingFunction> easings,
                                float duration,
                                float delay,
                                const std::string &label = "",
                                EasingCallback callback = ofxFunctional::defaultCallback)
{
    if(label == "") {
        string new_label = std::string("ofe::") + ofToString(ofGetUnixTime()) + "_" + ofToString(ofRandom(0.0f, 1.0f));
        ofxFunctional::Easing::factory(easings, duration, delay, new_label, callback);
        return new_label;
    } else {
        ofxFunctional::Easing::factory(easings, duration, delay, label, callback);
        return label;
    }
}

inline std::string ofxFunctionalEasing(std::vector<EasingFunction> easings,
                                       float duration,
                                       const std::string &label = "",
                                       EasingCallback callback = ofxFunctional::defaultCallback)
{
    return ofxFunctionalEasing(easings, duration, 0.0f, label, callback);
}

std::string ofxFunctionalEasing(std::initializer_list<EasingFunction> easings,
                                float duration,
                                float delay,
                                const std::string &label = "",
                                EasingCallback callback = ofxFunctional::defaultCallback)
{
    if(label == "") {
        string new_label = std::string("ofe::") + ofToString(ofGetUnixTime()) + "_" + ofToString(ofRandom(0.0f, 1.0f));
        ofxFunctional::Easing::factory(easings, duration, delay, new_label, callback);
        return new_label;
    } else {
        ofxFunctional::Easing::factory(easings, duration, delay, label, callback);
        return label;
    }
}

inline std::string ofxFunctionalEasing(std::initializer_list<EasingFunction> easings,
                                       float duration,
                                       const std::string &label = "",
                                       EasingCallback callback = ofxFunctional::defaultCallback)
{
    return ofxFunctionalEasing(easings, duration, 0.0f, label, callback);
}

inline std::string ofxFunctionalEasing(EasingFunction easing,
                                       float duration,
                                       float delay,
                                       const std::string &label = "",
                                       EasingCallback callback = ofxFunctional::defaultCallback)
{
    return ofxFunctionalEasing({easing}, duration, delay, label, callback);
}

inline std::string ofxFunctionalEasing(EasingFunction easing,
                                       float duration,
                                       const std::string &label = "",
                                       EasingCallback callback = ofxFunctional::defaultCallback)
{
    return ofxFunctionalEasing({easing}, duration, 0.0f, label, callback);
}