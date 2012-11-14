#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //at first you must specify the Ip address of this machine
    artnet.setup("192.168.11.100");
    
    ofSetFrameRate(40);
    fbo.allocate(512, 1);
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
        colorR = colorG = colorB = 0;
        ofSetColor(0, 200, 200);
        ofRect(0, 0, 512, 1);
        fbo.end();
        fbo.readToPixels(testImage.getPixelsRef());
    }

    //list nodes for sending
    //Artnet subnet and universe is fixed to 0x01
    artnet.sendDmx("192.168.11.101", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.102", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.103", testImage.getPixels(), 510);
    artnet.sendDmx("192.168.11.104", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.105", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.106", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.107", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.108", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.109", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.110", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.111", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.112", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.113", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.114", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.115", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.116", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.117", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.118", testImage.getPixels(), 512);
    artnet.sendDmx("192.168.11.119", testImage.getPixels(), 512);
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