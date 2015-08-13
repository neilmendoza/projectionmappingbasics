#include "ofApp.h"

const ofVec3f ofApp::BOX_DIMS = ofVec3f(26.65f, 26.65f, 11.f);

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // check whether we've previously saved meshes
    if (ofFile("wireframe.ply").exists() && ofFile("box.ply").exists())
    {
        // we have saved meshes so load them up
        wireframeMesh.load("wireframe.ply");
        boxMesh.load("box.ply");
    }
    else
    {
        // create a new box mesh that is the dimensions that we have measured
        wireframeMesh = ofMesh::box(BOX_DIMS.x, BOX_DIMS.y, BOX_DIMS.z);
    
        // create a new box mesh that is the dimensions that we want
        // we make the dimensions very slightly smaller than the dimensions
        // of the outline of the box so that the computer knows that the
        // outline is to be rendered outside of the box and we can use
        // it to hide the outline at the back of the box
        boxMesh = ofMesh::box(.999f * BOX_DIMS.x, .999f * BOX_DIMS.y, .999f * BOX_DIMS.z);
    }
    
    // set the camera in the meshes, this is needed so that we know
    // how to translate from screen coordinates to world coordinated to be able
    // to pick points to warp
    wireframeMesh.setCamera(projector);
    boxMesh.setCamera(projector);
    
    // put our projector 200cm away from our object that will be at the origin
    projector.setPosition(0, 0, -200.f);
    
    // set our camera's vertical field of view
    // this can be calculated using this spreadsheet
    // https://docs.google.com/spreadsheets/d/136NbNeFGER7yiOVgik7hueTRkYGkNHcqBlRFdfcix7I/edit#gid=0
    projector.setFov(16.84f);
    
    // look at the origin where our box is
    projector.lookAt(ofVec3f(0.f, 0.f, 0.f));
    
    // add functions to be called when the projector position and tilt are changed
    // and the boxAngle in relation to the camera
    projectorPosition.addListener(this, &ofApp::projectorPositionChanged);
    projectorTilt.addListener(this, &ofApp::projectorTiltChanged);
    boxAngle.addListener(this, &ofApp::boxAngleChanged);
                         
    // add functions to be called when the tweakMesh button is enabled and disabled
    tweakMesh.addListener(this, &ofApp::tweakMeshChanged);
    
    // set up user interface so we can tweak the projection
    gui.setup();
    gui.add(boxAngle.set("boxAngle", 0.f, -90.f, 90.f));
    gui.add(projectorTilt.set("projectorTilt", 0.f, -30.f, -10.f));
    gui.add(projectorPosition.set("projectorPosition",
                                  ofVec3f(0.f, 0.f, -200.f),
                                  ofVec3f(-10.f, 20.f, -150.f),
                                  ofVec3f(10.f, 50.f, -100.f)));
    gui.add(tweakMesh.set("tweakMesh", false));
    
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
    
    // draw the selected vertices for mesh warping
    boxMesh.drawSelectedVertices();
    
    // now draw a glowing green outline
    ofSetColor(255);
    ofSetLineWidth(2.f);
    wireframeMesh.drawWireframe();
    
    // draw the selected vertices for mesh warping
    wireframeMesh.drawSelectedVertices();
    
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
    
    // save the meshes
    boxMesh.save("box.ply");
    wireframeMesh.save("wireframe.ply");
}

void ofApp::projectorPositionChanged(ofVec3f& projectorPosition)
{
    projector.setPosition(projectorPosition);	
}

void ofApp::projectorTiltChanged(float& projectorTilt)
{
    // get the current orientation
    ofVec3f orientation = projector.getOrientationEuler();
    
    // change the tilt (x rotation)
    projector.setOrientation(ofVec3f(projectorTilt, orientation.y, orientation.z));
}

void ofApp::tweakMeshChanged(bool& tweakMesh)
{
    // enable or disable tweaking of these meshes
    wireframeMesh.setEventsEnabled(tweakMesh);
    boxMesh.setEventsEnabled(tweakMesh);
}

void ofApp::boxAngleChanged(float& boxAngle)
{
    ofMatrix4x4 rotation = ofMatrix4x4::newRotationMatrix(boxAngle, ofVec3f(0.f, 1.f, 0.f));
    boxMesh.setTransform(rotation);
    wireframeMesh.setTransform(rotation);
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
