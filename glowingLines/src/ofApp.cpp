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

//--------------------------------------------------------------
void ofApp::setup()
{
    // set some openFrameworks settings
    ofSetFrameRate(60);
    ofBackground(0);
    
    // check whether we've previously saved meshes
    if (ofFile("outline.ply").exists() && ofFile("box.ply").exists())
    {
        // we have saved meshes so load them up
        outlineMesh.load("outline.ply");
        outlineMesh.setMode(OF_PRIMITIVE_LINES);
        boxMesh.load("box.ply");
    }
    else
    {
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
        
        // create the box mesh
        // we make the dimensions very slightly smaller than the dimensions
        // of the outline of the box so that the computer knows that the
        // outline is to be rendered outside of the box and we can use
        // it to hide the outline at the back of the box
        boxMesh = ofMesh::box(.999f * BOX_DIMS.x, .999f * BOX_DIMS.y, .999f * BOX_DIMS.z, 1, 1, 1);
    }
    
    // set the camera in the meshes, this is needed so that we know
    // how to translate from screen coordinates to world coordinated to be able
    // to pick points to warp
    outlineMesh.setCamera(projector);
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
    
    // initialise the post processing
    outlineEffects.init();
    
    // add a bloom (glow) pass to the post processing chain
    outlineEffects.createPass<BloomPass>();
    outlineEffects.createPass<FxaaPass>();
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    // look at the scene from the perspective of the projector
    // when using ofxPostProcessing with a camera object we do this
    // by passing the camera to the ofxPostProcessing::begin()
    // function as an argument
    outlineEffects.begin(projector);
    
    // rotate our box around the y axis
    // so it's not face on to the projector
    ofPushMatrix();
    ofRotateY(boxAngle);
    
    // enable depth testing so that the box mesh masks
    // the outline at the back of the box
    ofEnableDepthTest();
    
    // draw our box mesh in dark grey
    ofSetColor(20);
    boxMesh.draw();
    
    // we set the line width of the box to be drawn to 3
    // I'm using this function for convenience, however please note
    // that this function does not work if you are using the programmable
    // renderer in openFrameworks as it is based on functionality no
    // longer present in newer versions of OpenGL
    ofSetLineWidth(4.f);
    
    // now draw a glowing green outline
    ofSetColor(0, 255, 0);
    outlineMesh.draw();
    
    // disable depth testing
    ofDisableDepthTest();
    
    // reset the transform to what it was before we rotated it
    ofPopMatrix();
    
    // finish drawing the scene from the perspective of the projector
    outlineEffects.end();
}

void ofApp::exit()
{
    // save the settings
    gui.saveToFile("settings.xml");
    
    // save the meshes
    boxMesh.save("box.ply");
    outlineMesh.save("outline.ply");
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
    outlineMesh.setEventsEnabled(tweakMesh);
    boxMesh.setEventsEnabled(tweakMesh);
}

void ofApp::boxAngleChanged(float& boxAngle)
{
    ofMatrix4x4 rotation = ofMatrix4x4::newRotationMatrix(boxAngle, ofVec3f(0.f, 1.f, 0.f));
    boxMesh.setTransform(rotation);
    outlineMesh.setTransform(rotation);
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
