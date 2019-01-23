#include "ofxArtnetReceiver.h"



ofxArtnetReceiver::ofxArtnetReceiver()
{
	receivedData = NULL;
}


ofxArtnetReceiver::~ofxArtnetReceiver()
{
	if (isThreadRunning())
	{
		stopThread();
		waitForThread(false);
	}
}

void ofxArtnetReceiver::setup(const int universe,const int port)
{
	ofxUDPSettings settings;
	this->universe = universe;
	settings.receiveOn(port);
	settings.blocking = false;
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
	std::unique_lock<std::mutex> lock(mutex);
	memcpy(data, receivedData, size);
}


void ofxArtnetReceiver::threadedFunction()
{
	while (isThreadRunning())
	{
		char *data = new char[HEADER_LENGTH+512];
		udp.Receive(data, HEADER_LENGTH+512);
		string protcol_id(data, 7);
		if (protcol_id == "Art-Net")
		{
			isDataNew = true;
			size = (data[HEADER_LENGTH - 2] << 8) + (data[HEADER_LENGTH - 1] & 0xff);
			int dataUniverse = (data[HEADER_LENGTH - 4] & 0xff) + (data[HEADER_LENGTH - 3] << 8);
			if (dataUniverse == universe)
			{
				std::unique_lock<std::mutex> lock(mutex);
				if (receivedData != NULL)
				{
					delete[] receivedData;
				}
				receivedData = new char[size];
				memcpy(receivedData, data + HEADER_LENGTH, size);
			}
		}
		delete[] data;
	}
}
