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
    
    ///////////////////////////////////////////////////////////////////////
    
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
    
    ///////////////////////////////////////////////////////////////////////
    
    // put our projector 200cm away from our object that will be at the origin
    projector.setPosition(0, 0, -200.f);
    
    // set our camera's vertical field of view
    // this can be calculated using this spreadsheet
    // https://docs.google.com/spreadsheets/d/136NbNeFGER7yiOVgik7hueTRkYGkNHcqBlRFdfcix7I/edit#gid=0
    projector.setFov(16.84f);
    
    // position our object at the origin (0, 0, 0)
    projector.lookAt(ofVec3f(0.f, 0.f, 0.f));
    
    // add functions to be called when the projector position and tilt are changed
    projectorPosition.addListener(this, &ofApp::projectorPositionChanged);
    projectorTilt.addListener(this, &ofApp::projectorTiltChanged);
    
    // set up user interface so we can tweak the projector position
    gui.setup();
    gui.add(boxAngle.set("boxAngle", 0.f, -90.f, 90.f));
    gui.add(projectorTilt.set("projectorTilt", 0.f, -30.f, -10.f));
    gui.add(projectorPosition.set("projectorPosition",
                                  ofVec3f(0.f, 0.f, -200.f),
                                  ofVec3f(-10.f, 20.f, -150.f),
                                  ofVec3f(10.f, 50.f, -100.f)));
    
    // load the settings from the previous time we ran the application
    gui.loadFromFile("settings.xml");
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
    projector.begin();
    
    // enable depth testing so that the box mesh masks
    // the outline at the back of the box
    ofEnableDepthTest();
    
    // rotate our box so by 45 degrees around the y axis
    // so it's not face on to the projector
    ofPushMatrix();
    ofRotateY(boxAngle);
    
    // draw our box mesh in dark grey
    ofSetColor(20);
    boxMesh.draw();
    
    // now draw the outline
    ofSetColor(255);
    outlineMesh.drawWireframe();
    
    // reset the transform to what it was before we rotated it
    ofPopMatrix();
    
    // disable depth testing
    ofDisableDepthTest();
    
    // finish drawing the 3d scene from the point of view
    // of the projector
    projector.end();
    
    // draw the user interface
    gui.draw();
}

void ofApp::exit()
{
    // save the settings
    gui.saveToFile("settings.xml");
}

void ofApp::projectorPositionChanged(ofVec3f& projectorPosition)
{
    projector.setPosition(projectorPosition);	
}

void ofApp::projectorTiltChanged(float& projectorTilt)
{
    ofVec3f orientation = projector.getOrientationEuler();
    projector.setOrientation(ofVec3f(projectorTilt, orientation.y, orientation.z));
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
