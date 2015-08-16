#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxGui.h"
#include "ofxWarpableMesh.h"

class ofApp : public ofBaseApp
{
public:
    static const ofVec3f BOX_DIMS;
    
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    void projectorPositionChanged(ofVec3f& projectorPosition);
    void projectorTiltChanged(float& projectorTilt);
    
    ofCamera projector;
    ofVboMesh boxMesh;
    ofVboMesh wireframeMesh;
    
    // user interface
    ofxPanel gui;
    ofParameter<ofVec3f> projectorPosition;
    ofParameter<float> projectorTilt;
    ofParameter<float> boxAngle;
};
