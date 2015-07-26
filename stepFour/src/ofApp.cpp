#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // create a new box mesh that is the dimensions that we want
    // 10 cm by 10cm by 10cm in our case
    boxMesh = ofMesh::box(50.f, 50.f, 50.f);
    
    // put our projector 200cm away from our object that will be at the origin
    projector.setPosition(0, 0, -200.f);
    
    // set our camera's vertical field of view
    // this can be calculated using this spreadsheet
    // https://docs.google.com/spreadsheets/d/136NbNeFGER7yiOVgik7hueTRkYGkNHcqBlRFdfcix7I/edit#gid=0
    projector.setFov(30.f);
    
    projector.lookAt(ofVec3f(0.f, 0.f, 0.f));
    
    light.setPosition(100.f, 100.f, 100.f);
    light.enable();
    
    catImage.loadImage("cat.jpg");
    
    catEffects.init();
    catEffects.setFlip(true);
    noiseWarpPass = catEffects.createPass<NoiseWarpPass>();
    hsbShiftPass = catEffects.createPass<HsbShiftPass>();
    catEffects.createPass<BloomPass>();
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    // warp our cat
    hsbShiftPass->setHueShift(1.f + sin(ofGetElapsedTimef()));
    noiseWarpPass->setAmplitude(ofMap(sin(0.5f * ofGetElapsedTimef()), -1.f, 1.f, 0.f, .1f));
    catEffects.begin();
    catImage.draw(0.f, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    catEffects.end(false);
    
    // look at the scene from the perspective of the projector
    projector.begin();
    
    ofEnableDepthTest();
    
    // rotate our box so by 45 degrees around the y axis
    // so it's not face on to the projector
    ofPushMatrix();
    ofRotateY(45);
    
    // now draw our box mesh
    catEffects.getProcessedTextureReference().bind();
    boxMesh.draw();
    catEffects.getProcessedTextureReference().unbind();
    
    // reset the transform to what it was before we rotated it
    ofPopMatrix();
    
    ofDisableDepthTest();
    
    // finish drawing the scene from the perspective of the projector
    projector.end();
    
    syphon.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
