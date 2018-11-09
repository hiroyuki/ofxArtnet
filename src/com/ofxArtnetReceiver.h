#pragma once
#include "ofxArtnetProtocol.h"

class ofxArtnetReceiver : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetReceiver();
	~ofxArtnetReceiver();

	void setup(int port = 6454);

	bool hasNextMessage() const;
	void getData(unsigned char * data);
	int getDataSize();
protected:
	void threadedFunction();
	std::condition_variable condition;
	bool isDataNew = false;
	int size;
	char* receivedData;
};

