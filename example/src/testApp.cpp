#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //put your if ip
    artnet.setup("192.168.11.18");
    testImage.loadImage("test.png");
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2)); 
    //list nodes for sending
    artnet.sendDmx("192.168.11.53", testImage.getPixels(), 510);
    artnet.sendDmx("192.168.11.52", testImage.getPixels(), 510);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 0);
    ofCircle( 100, 100, 100 );
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