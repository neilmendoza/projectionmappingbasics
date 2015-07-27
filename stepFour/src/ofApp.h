#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "HsbShiftPass.h"

class ofApp : public ofBaseApp
{
public:
    static const ofVec3f BOX_DIMS;
    static const unsigned NUM_BOX_VERTICES = 8;
    static const ofVec3f BOX_VERTICES[NUM_BOX_VERTICES];
    static const unsigned NUM_OUTLINE_INDICES = 24;
    static const unsigned OUTLINE_INDICES[NUM_OUTLINE_INDICES];
    static const unsigned NUM_FFT_BANDS = 16;
    
    void setup();
    void update();
    void draw();

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
    ofVboMesh boxMesh;
    ofVboMesh outlineMesh;
    ofCamera projector;
    ofLight light;
    ofxPostProcessing outlineEffects;
    
    // sound
    ofSoundPlayer soundPlayer;
    float smoothedFft[NUM_FFT_BANDS];
    float maxFft[NUM_FFT_BANDS];
    float normalisedFft[NUM_FFT_BANDS];
    
    // cat stuff
    ofImage catImage;
    ofxPostProcessing catEffects;
    HsbShiftPass::Ptr hsbShiftPass;
    NoiseWarpPass::Ptr noiseWarpPass;
};
