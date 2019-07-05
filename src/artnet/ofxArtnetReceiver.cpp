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
	return !receivedDataChannel.empty();
}

void ofxArtnetReceiver::getData(ofxArtnetMessage& m)
{
    if(!hasMessage()) {
        ofLogWarning("ofxArtnet") << "no new data. copy previous data.";
    }
    while(hasMessage()) {
        receivedDataChannel.receive(receivedData);
    }
    m = receivedData;
}

void ofxArtnetReceiver::getNextData(ofxArtnetMessage& m)
{
    if(hasMessage()) {
        receivedDataChannel.receive(receivedData);
    } else {
        ofLogWarning("ofxArtnet") << "no new data. copy previous data.";
    }
    m = receivedData;
}

void ofxArtnetReceiver::threadedFunction()
{
    unsigned char data[HEADER_LENGTH + 512];
	while (isThreadRunning())
	{
        memset(data, 0, HEADER_LENGTH + 512);
		udp.Receive((char *)data, HEADER_LENGTH + 512);
		std::string protcol_id((char *)data, 7);
		if (protcol_id == "Art-Net")
		{
			if (data[8] == (OP_OUTPUT & 0xff) && data[9] == ((OP_OUTPUT >> 8) & 0xff))
			{
                ofxArtnetMessage receivedData;
				int versionHi = data[HEADER_LENGTH-8];
				int versionLo = data[HEADER_LENGTH-7];
				int seq = data[HEADER_LENGTH-6];
				int physical = data[HEADER_LENGTH-5];
				receivedData._portAddress = data[HEADER_LENGTH-4] + (data[HEADER_LENGTH-3] << 8);
				int dataSize = (data[HEADER_LENGTH - 2] << 8) + (data[HEADER_LENGTH - 1] & 0xff);
                receivedData.setData(data + HEADER_LENGTH, dataSize);
				receivedDataChannel.send(receivedData);
			}
		}
	}
}
