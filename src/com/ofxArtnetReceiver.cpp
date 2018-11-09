#include "ofxArtnetReceiver.h"



ofxArtnetReceiver::ofxArtnetReceiver()
{

}


ofxArtnetReceiver::~ofxArtnetReceiver()
{
	std::unique_lock<std::mutex> lck(mutex);
	stopThread();
	condition.notify_all();
	waitForThread(false);
}

void ofxArtnetReceiver::setup(int port)
{
	ofxUDPSettings settings;
	
	settings.receiveOn(port);
	settings.blocking = true;
	udp.Setup(settings);
	startThread();

}

bool ofxArtnetReceiver::hasNextMessage() const
{
	return isDataNew;
}


int ofxArtnetReceiver::getDataSize()
{
	return this->size;
}

void ofxArtnetReceiver::getData(unsigned char * data)
{
	if (isDataNew)
	{
		std::unique_lock<std::mutex> lock(mutex);
		memcpy(data, receivedData, size);
		condition.notify_all();
	}
}


void ofxArtnetReceiver::threadedFunction()
{
	while (isThreadRunning())
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (isDataNew)//reset
		{
			isDataNew = false;
			delete[] receivedData;
		}
		char *data = new char[HEADER_LENGTH+512];
		udp.Receive(data, HEADER_LENGTH+512);
		string protcol_id(data, 7);
		if (protcol_id == "Art-Net")
		{
			isDataNew = true;
			size = (data[HEADER_LENGTH - 2] << 8) + (data[HEADER_LENGTH - 1] & 0xff);
			receivedData = new char[size];
			memcpy(receivedData, data + HEADER_LENGTH, size);
		}
		delete[] data;
		condition.wait(lock);
	}
}
