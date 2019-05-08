#pragma once
#include "ofxArtnetProtocol.h"
#include "ofxArtnetMessage.h"

class ofxArtnetSender : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetSender();
	ofxArtnetSender(const ofxArtnetSender& origin);

	~ofxArtnetSender();
	void setup(const string ipAdress, const short port = 6454);

	inline void setThreadedSend(const bool threaded)
	{
		bThreadEnabled = threaded;
	}

	void setFrameRate(const float fps)
	{
		framerate = fps;
		interval = 1000.0 / framerate;
	}

	void start(const float fps)
	{
		setFrameRate(fps);
		startThread();
	}

	void sendArtnet(const ofxArtnetMessage& message);
	
protected:
	bool bThreadEnabled = false;
	void threadedFunction();

	string targetIp;
	short targetPort;
	float framerate = 40;
	float interval = 25;

	ofxArtnetMessage _message;
	void createBuffer(const ofxArtnetMessage& message, vector<unsigned char>& data);
	void sendData(const ofxArtnetMessage& message);
};

