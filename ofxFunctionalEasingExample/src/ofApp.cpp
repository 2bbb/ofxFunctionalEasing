#include "ofMain.h"
#include "ofxFunctionalEasing.h"

class ofApp : public ofBaseApp {
    struct Circle {
        float radius;
        float x, y;
        int alpha;
        Circle(float r, float x, float y)
        : radius(r)
        , x(x)
        , y(y)
        , alpha(0) {}
        
        void draw() {
            ofSetColor(255, 255, 255, alpha);
            ofDrawCircle(x, y, radius);
        }
    };
    int generatedNum;
    vector<shared_ptr<Circle>> circles;
public:
    void setup() {
        generatedNum = 0;
    }
    
    void draw() {
        ofBackground(0, 0, 0);
        for(auto circle : circles) {
            circle->draw();
        }
    }
    
    void keyPressed(int key) {
        if(key == ' ') {
            for(int i = 0; i < 100; i++) {
                float from = ofRandom(5, 20), to = from + ofRandom(10, 30);
                shared_ptr<Circle> c = shared_ptr<Circle>(new Circle(from, ofRandomWidth(), ofRandomHeight()));
                
                circles.push_back(c);
                auto &circle = circles.back();
                vector<EasingFunction> eases;
                
                if(ofRandom(1) < 0.8f) {
                    eases.push_back([=](float progress) {
                        circle->radius = ofLerp(from, to, progress * progress);
                        circle->alpha = ofLerp(255, 0, progress);
                    });
                } else {
                    circle->alpha = 255;
                    eases.push_back(BindEase(ofxFunctional::OutQuad, circle->radius, circle->radius, 100.0f));
                    eases.push_back(BindEase(ofxFunctional::OutQubic, circle->alpha, 255, 0));
                }
                
                ofxFunctionalEasing(eases, ofRandom(0.5f, 0.8f), ofRandom(0.0f, 0.3f), ofToString(generatedNum++), [&,circle](std::string label) {
                    ofRemove(circles, [=](shared_ptr<Circle> &x) { return x == circle; });
                });
            }
        }
    }
};

int main() {
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
}
