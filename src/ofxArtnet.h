#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"
class ofxArtnet
{
public:
	ofxArtnet();
	~ofxArtnet();


	void setup(const string ipAdress, const short port = 6454);
	void sendArtnet(const ofPixels data, const int universe = 0);
private:
	ofxUDPManager udp;
	const string HEAD = "Art-Net";
	const short OP_OUTPUT = 0x5000;
};

