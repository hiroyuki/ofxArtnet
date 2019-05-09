#pragma once
#include "ofxArtnetProtocol.h"
#include "ofxArtnetMessage.h"
class ofxArtnetReceiver : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetReceiver();
	~ofxArtnetReceiver();

	void setup(const uint16_t port = 6454);

	bool hasMessage() const;
	void getData(ofxArtnetMessage& m);
protected:
	void threadedFunction();
	bool isDataNew = false;
	int size;
	ofxArtnetMessage receivedData;
};

