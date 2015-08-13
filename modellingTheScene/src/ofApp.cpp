#include "ofApp.h"

const ofVec3f ofApp::BOX_DIMS = ofVec3f(26.65f, 26.65f, 11.f);

const ofVec3f ofApp::BOX_VERTICES[] = {
    //back
    ofVec3f(-.5f * BOX_DIMS.x, -.5f * BOX_DIMS.y, -.5f * BOX_DIMS.z),
    ofVec3f(.5f * BOX_DIMS.x, -.5f * BOX_DIMS.y, -.5f * BOX_DIMS.z),
    ofVec3f(.5f * BOX_DIMS.x, .5f * BOX_DIMS.y, -.5f * BOX_DIMS.z),
    ofVec3f(-.5f * BOX_DIMS.x, .5f * BOX_DIMS.y, -.5f * BOX_DIMS.z),
    
    // front
    ofVec3f(-.5f * BOX_DIMS.x, -.5f * BOX_DIMS.y, .5f * BOX_DIMS.z),
    ofVec3f(.5f * BOX_DIMS.x, -.5f * BOX_DIMS.y, .5f * BOX_DIMS.z),
    ofVec3f(.5f * BOX_DIMS.x, .5f * BOX_DIMS.y, .5f * BOX_DIMS.z),
    ofVec3f(-.5f * BOX_DIMS.x, .5f * BOX_DIMS.y, .5f * BOX_DIMS.z)
};

const unsigned ofApp::OUTLINE_INDICES[] = {
    // back
    0,1, 1,2, 2,3, 3,0,
    // front
    4,5, 5,6, 6,7, 7,4,
    // sides
    0,4, 1,5, 2,6, 3,7
};

const unsigned ofApp::FACE_INDICES[] = {
    // back
    0, 1, 2, 0, 2, 3,
    
    // front
    4, 5, 6, 4, 6, 7,
    
    // left
    0, 4, 7, 0, 7, 3,
    
    // right
    1, 5, 6, 1, 6, 2,
    
    // top
    0, 1, 5, 0, 5, 4,
    
    // bottom
    3, 2, 6, 3, 6, 7
};

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // create an outline of a box using a mesh in OF_PRIMITIVE_LINES mode
    // so that every two vertices represents a line
    outlineMesh.setMode(OF_PRIMITIVE_LINES);
    
    // add in all the vertices to the mesh
    for (unsigned i = 0; i < NUM_BOX_VERTICES; ++i)
    {
        outlineMesh.addVertex(BOX_VERTICES[i]);
    }
    
    // rather than adding each vertex multiple times, we add
    // indices that point to where the appropriate vertices
    // are for each line in the outline
    for (unsigned i = 0; i < NUM_OUTLINE_INDICES; ++i)
    {
        outlineMesh.addIndex(OUTLINE_INDICES[i]);
    }
    
    // create a box mesh using OF_PRIMITIVE_TRIANGLES
    // this is a mesh where every 3 vertices represents a triangle
    boxMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    // add in all the vertices of the box
    // we make the dimensions very slightly smaller than the dimensions
    // of the outline of the box so that the computer knows that the
    // outline is to be rendered outside of the box and we can use
    // it to hide the outline at the back of the box
    for (unsigned i = 0; i < NUM_BOX_VERTICES; ++i)
    {
        boxMesh.addVertex(.999f * BOX_VERTICES[i]);
    }
    
    // rather than adding each vertex multiple times, we add
    // indices that point to where the appropriate vertices
    // are for each triangle in the mesh
    for (unsigned i = 0; i < NUM_FACE_INDICES; ++i)
    {
        boxMesh.addIndex(FACE_INDICES[i]);
    }
    
    // move the camera so that it's 100cm away from the origin
    camera.setDistance(100.f);
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
    
    // now draw the outline
    ofSetColor(255);
    outlineMesh.drawWireframe();
    
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
