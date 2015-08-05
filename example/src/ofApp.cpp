#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //at first you must specify the Ip address of this machine
    artnet.setup("10.0.0.4"); //make sure the firewall is deactivated at this point
    
    ofSetFrameRate(40);
    fbo.allocate(512, 1, GL_RGB);
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    //create send buffer by ofFbo
    {
        fbo.begin();
        ofClear(0);
        float colorR = (sin(ofGetElapsedTimeMillis() / 1000.f) / 2.f + 0.5f) * 255.f;
        float colorG = (sin((ofGetElapsedTimeMillis() / 1000.f) + PI / 3.f) / 2.f + 0.5f) * 255.f;
        float colorB = (sin((ofGetElapsedTimeMillis() / 1000.f)  + PI * 2.f / 3.f) / 2.f + 0.5f) * 255.f;
        ofSetColor((int)colorR, (int)colorG, (int)colorB);
        ofRect(0, 0, 512, 1);
        fbo.end();
        fbo.readToPixels(testImage.getPixelsRef());
    }

    //list nodes for sending
    //with subnet / universe
//    artnet.sendDmx("10.0.0.149", 0xf, 0xf, testImage.getPixels(), 512);
    artnet.sendDmx("10.0.0.149", testImage.getPixels(), 512);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    float scalex = ofGetWidth() / fbo.getWidth();
    float scaley = ofGetHeight() / fbo.getHeight();
    ofScale(scalex, scaley);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
