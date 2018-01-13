//
//  ofxFunctionalEasing.h
//
//  Created by ISHII 2bit on 2015/09/21.
//
//

#pragma once

#include "ofMain.h"
#include <functional>
#include <memory>
#include <unordered_map>

namespace ofxFunctional {
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

            void add(std::shared_ptr<Easing> easing, const std::string &label) {
                easings.insert(std::make_pair(label, easing));
            }
        };
        
        std::function<void(float perc)> easing;
        float duration, delay;
        std::string label;
        std::function<void(const std::string &)> callback;
        float startTime, endTime;
        Easing(std::function<void(float progress)> easing,
               float duration,
               float delay,
               const std::string &label,
               const std::function<void(const std::string &)> &callback)
        : easing(easing)
        , duration(duration)
        , delay(delay)
        , callback(callback)
        , label(label)
        {
            startTime = delay + ofGetElapsedTimef();
            endTime = startTime + duration;
        }
        
    public:
        static void factory(std::function<void(float)> easing,
                            float duration,
                            float delay,
                            const std::string &label,
                            const std::function<void(const std::string &)> &callback)
        {
            Manager::getManager()->add(std::shared_ptr<Easing>(new Easing(easing, duration, delay, label, callback)), label);
        }

        bool update(float time) {
            if(time < startTime) return false;
            float progress = ofMap(time, startTime, endTime, 0.0f, 1.0f, true);
            easing(progress);
            return 1.0f <= progress;
        }
        
        void finish() {
            callback(label);
        }
    };
};

static std::string ofxFunctionalEasing(std::function<void(float progress)> easing,
                                float duration,
                                float delay,
                                const std::string &label = "",
                                const std::function<void(const std::string &)> &callback = [](const std::string &){})
{
    if(label == "") {
        string new_label = std::string("ofe::") + ofToString(ofGetUnixTime()) + "_" + ofToString(ofRandom(0.0f, 1.0f));
        ofxFunctional::Easing::factory(easing, duration, delay, new_label, callback);
        return new_label;
    } else {
        ofxFunctional::Easing::factory(easing, duration, delay, label, callback);
        return label;
    }
}

inline static std::string ofxFunctionalEasing(std::function<void(float progress)> easing,
                                       float duration,
                                       const std::string &label = "",
                                       const std::function<void(const std::string &)> &callback = [](const std::string &){})
{
    ofxFunctionalEasing(easing, duration, 0.0f, label, callback);
}
