#pragma once
#include "ofxArtnetProtocol.h"

class ofxArtnetReceiver : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetReceiver();
	~ofxArtnetReceiver();

	void setup(const int universe = 0,const int port = 6454);

	bool hasNextMessage() const;
	void getData(unsigned char * data);
	int getDataSize();
protected:
	void threadedFunction();
	bool isDataNew = false;
	int size;
	int universe;
	char* receivedData;
};

