#include "ofApp.h"

const ofVec3f ofApp::BOX_DIMS = ofVec3f(26.65f, 26.65f, 11.f);

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // create a mesh that we will render as a wireframe so that we can
    // see where the edges of the box are
    wireframeMesh = ofMesh::box(BOX_DIMS.x, BOX_DIMS.y, BOX_DIMS.z, 1, 1, 1);
    
    // create a new box mesh that is the dimensions that we want
    // we make the dimensions very slightly smaller than the dimensions
    // of the outline of the box so that the computer knows that the
    // outline is to be rendered outside of the box and we can use
    // it to hide the outline at the back of the box
    boxMesh = ofMesh::box(.999f * BOX_DIMS.x, .999f * BOX_DIMS.y, .999f * BOX_DIMS.z, 1, 1, 1);
    
    // position the camera 100 cm away
    camera.setDistance(50.f);
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
    // the wireframe at the back of the box
    ofEnableDepthTest();
    
    // draw our box mesh in black
    ofSetColor(0);
    boxMesh.draw();
    
    // now draw a the wireframe
    ofSetColor(255);
    wireframeMesh.drawWireframe();
    
    // disable depth testing
    ofDisableDepthTest();
    
    // finish drawing the 3d scene from the point of view
    // of the projector
    camera.end();
}

void ofApp::exit()
{
}

void ofApp::keyPressed(int key)
{
    if (key == 'f') ofToggleFullscreen();
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
