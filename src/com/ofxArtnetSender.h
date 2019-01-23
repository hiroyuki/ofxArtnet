#pragma once
#include "ofxArtnetProtocol.h"

class ofxArtnetSender : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetSender();
	~ofxArtnetSender();
	void setup(const string ipAdress, const int universe=0, const short port = 6454);

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

	void sendArtnet(const ofPixels data);
	void sendArtnet(const unsigned char* data, const int size);
	
protected:
	bool bThreadEnabled = false;
	void threadedFunction();

	int universe;
	unsigned char *_data;
	int _datasize;
	float framerate = 40;
	float interval = 25;

	void setData(const unsigned char* data, const int size)
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (_data == NULL)
		{
			_data = new unsigned char[size];
		}
		memcpy(_data, data, size);
		_datasize = size;
	}

	void sendData(const unsigned char* data, const int size);
};

