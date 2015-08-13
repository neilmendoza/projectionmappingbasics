#include "ofApp.h"

const ofVec3f ofApp::BOX_DIMS = ofVec3f(12.6f, 25.4f, 18.2f	);
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
    
    // create a new box mesh that is the dimensions that we want
    // we make the dimensions very slightly smaller than the dimensions
    // of the outline of the box so that the computer knows that the
    // outline is to be rendered outside of the box and we can use
    // it to hide the outline at the back of the box
    boxMesh = ofMesh::box(.999f * BOX_DIMS.x, .999f * BOX_DIMS.y, .999f * BOX_DIMS.z);
    
    // create an outline mesh using OF_PRIMITIVE_LINES mode
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
    
    // put our projector 200cm away from our object that will be at the origin
    projector.setPosition(0, 0, -200.f);
    
    // set our camera's vertical field of view
    // this can be calculated using this spreadsheet
    // https://docs.google.com/spreadsheets/d/136NbNeFGER7yiOVgik7hueTRkYGkNHcqBlRFdfcix7I/edit#gid=0
    projector.setFov(30.f);
    
    projector.lookAt(ofVec3f(0.f, 0.f, 0.f));
    
    light.setPosition(1000.f, 100.f, 100.f);
    light.enable();
    ofDisableLighting();
    
    // load the cat image
    catImage.load("cat.jpg");
    
    // initialise the cat effects
    catEffects.init();
    catEffects.setFlip(true);
    noiseWarpPass = catEffects.createPass<NoiseWarpPass>();
    hsbShiftPass = catEffects.createPass<HsbShiftPass>();
    
    // initialise the outline effects
    outlineEffects.init();
    
    // add a bloom (glow) pass and an FXAA (anti-aliasing) pass
    // to the post processing chain
    outlineEffects.createPass<BloomPass>();
    outlineEffects.createPass<FxaaPass>();
}

//--------------------------------------------------------------
void ofApp::update()
{
    // update the cat effect parameters
    hsbShiftPass->setHueShift(1.f + sin(ofGetElapsedTimef()));
    noiseWarpPass->setAmplitude(ofMap(sin(0.5f * ofGetElapsedTimef()), -1.f, 1.f, 0.f, .1f));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // warp our cat
    catEffects.begin();
    catImage.draw(0.f, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    catEffects.end(false);
    
    // look at the scene from the perspective of the projector
    // when using ofxPostProcessing with a camera object we do this
    // by passing the camera to the ofxPostProcessing::begin()
    // function as an argument
    outlineEffects.begin(projector);
    
    // rotate our box so by 45 degrees around the y axis
    // so it's not face on to the projector
    ofPushMatrix();
    ofRotateY(45);
    
    // enable depth testing so that the box mesh masks
    // the outline at the back of the box
    ofEnableDepthTest();
    
    // we set the line width of the box to be drawn to 3
    // I'm using this function for convenience, however please note
    // that this function does not work if you are using the programmable
    // renderer in openFrameworks as it is based on functionality no
    // longer present in newer versions of OpenGL
    ofSetLineWidth(4.f);
    
    // draw our box mesh in dark grey
    ofEnableLighting();
    catEffects.getProcessedTextureReference().bind();
    boxMesh.draw();
    catEffects.getProcessedTextureReference().unbind();
    ofDisableLighting();
    
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
