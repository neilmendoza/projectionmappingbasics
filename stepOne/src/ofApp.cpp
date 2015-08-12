#include "ofApp.h"

const ofVec3f ofApp::BOX_DIMS = ofVec3f(50.f, 50.f, 50.f);

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // create a new box mesh that is the dimensions that we have measured
    boxMesh = ofMesh::box(BOX_DIMS.x, BOX_DIMS.y, BOX_DIMS.z);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    // start drawing the 3d scene from the point of view
    // of the camera
    camera.begin();
    
    // enable depth testing so that the box mesh masks
    // the outline at the back of the box
    ofEnableDepthTest();
    
    // draw our box mesh in dark grey
    ofSetColor(20);
    boxMesh.draw();
    
    // now draw a glowing green outline
    ofSetColor(255);
    boxMesh.drawWireframe();
    
    // disable depth testing
    ofDisableDepthTest();
    
    // finish drawing the 3d scene from the point of view
    // of the projector
    camera.end();
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
