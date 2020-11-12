#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sendData.allocate(170, 1, GL_RGB);
	receiver.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (receiver.hasMessage())
	{
		ofxArtnetMessage m;
		receiver.getData(m);
		dataSize = m.getSize();
		data = new unsigned char[m.getSize()];
		m.readTo(data);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	for (int i = 0; i < dataSize; i++)
	{
		ofPushStyle();
		if(i%3==0) ofSetColor(ofColor::red);
		else if (i % 3 == 1) ofSetColor(ofColor::green);
		else if (i % 3 == 2) ofSetColor(ofColor::blue);
		float value = data[i] / 255.0;
		ofDrawRectangle(i * 6, ofGetHeight() - value*ofGetHeight(), 2, value*ofGetHeight());
		ofPopStyle();
	}
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(),2), 20, 20);
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
