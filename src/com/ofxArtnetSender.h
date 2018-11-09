#pragma once
#include "ofxArtnetProtocol.h"

class ofxArtnetSender : public ofxArtnetProtocol
{
public:
	ofxArtnetSender();
	~ofxArtnetSender();
	void setup(const string ipAdress, const short port = 6454);
	void sendArtnet(const ofPixels data, const int universe = 0);
	void sendArtnet(const unsigned char* data, const int size, const int universe = 0);
};

