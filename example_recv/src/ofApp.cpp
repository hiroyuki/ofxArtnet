#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sendData.allocate(170, 1, GL_RGB);
	receiver.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (receiver.hasNextMessage())
	{
		dataSize = receiver.getDataSize();
		data = new unsigned char[dataSize];
		receiver.getData(data);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(ofColor::lightGreen);
	for (int i = 0; i < dataSize; i++)
	{
		//cout << i << " ";
		float value = data[i] / 255.0;
		ofLine(i * 2, ofGetHeight() - (1 - value)*ofGetHeight(), i * 2, ofGetHeight());
	}
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 20, 20);
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
