#include "ofxArtnetReceiver.h"

ofxArtnetReceiver::ofxArtnetReceiver()
{
}


ofxArtnetReceiver::~ofxArtnetReceiver()
{
	if (isThreadRunning())
	{
		stopThread();
		waitForThread(false);
	}
}

void ofxArtnetReceiver::setup(const uint16_t port)
{
	ofxUDPSettings settings;
	settings.receiveOn(port);
	settings.blocking = false;
	udp.Setup(settings);
	startThread();

}

bool ofxArtnetReceiver::hasMessage() const
{
	return isDataNew;
}

void ofxArtnetReceiver::getData(ofxArtnetMessage& m)
{
	std::unique_lock<std::mutex> lock(mutex);
	m = receivedData;
}


void ofxArtnetReceiver::threadedFunction()
{
	while (isThreadRunning())
	{
		char *data = new char[HEADER_LENGTH + 512];
		udp.Receive(data, HEADER_LENGTH + 512);
		std::string protcol_id(data, 7);
		if (protcol_id == "Art-Net")
		{
			if (data[8] == (OP_OUTPUT & 0xff) && data[9] == ((OP_OUTPUT >> 8) & 0xff))
			{
				int versionHi = data[HEADER_LENGTH-8];
				int versionLo = data[HEADER_LENGTH-7];
				int seq = data[HEADER_LENGTH-6];
				int physical = data[HEADER_LENGTH-5];
				receivedData._portAddress = data[HEADER_LENGTH-4] + (data[HEADER_LENGTH-3] << 8);
				int dataSize = (data[HEADER_LENGTH - 2] << 8) + (data[HEADER_LENGTH - 1] & 0xff);
				receivedData.allocate(dataSize);
				isDataNew = true;
				memcpy(receivedData._data, data + HEADER_LENGTH, dataSize);
			}
		}
		delete[] data;
	}
}
