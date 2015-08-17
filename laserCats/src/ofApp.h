#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "HsbShiftPass.h"
#include "ofxWarpableMesh.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    static const ofVec3f BOX_DIMS;
    static const unsigned NUM_BOX_VERTICES = 8;
    static const ofVec3f BOX_VERTICES[NUM_BOX_VERTICES];
    static const ofVec2f TEX_COORDS[NUM_BOX_VERTICES];
    static const unsigned NUM_OUTLINE_INDICES = 24;
    static const unsigned OUTLINE_INDICES[NUM_OUTLINE_INDICES];
    static const unsigned NUM_FFT_BANDS = 8;
    
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
    void boxAngleChanged(float& boxAngle);
    
    ofCamera projector;
    ofxWarpableMesh boxMesh;
    ofxWarpableMesh outlineMesh;
    
    // user interface
    ofxPanel gui;
    ofParameter<ofVec3f> projectorPosition;
    ofParameter<float> projectorTilt;
    ofParameter<float> boxAngle;
    bool drawGui;
    
    // outline
    ofxPostProcessing outlineEffects;
    
    // this plays our audio file
    ofSoundPlayer soundPlayer;

    // these variables will hold the data related to the
    // levels of frequency bands in the sound file
    float smoothedFft[NUM_FFT_BANDS];
    float maxFft[NUM_FFT_BANDS];
    float normalisedFft[NUM_FFT_BANDS];

    // this frame buffer is where we will hold the eq
    ofFbo eqFbo;

    // this is our laser cat image
    ofImage catImage;
};
