#include "ofxArtnetSender.h"



ofxArtnetSender::ofxArtnetSender()
{
	_data = NULL;
}


ofxArtnetSender::~ofxArtnetSender()
{
	std::unique_lock<std::mutex> lck(mutex);
	stopThread();
	condition.notify_all();
	waitForThread(false);
}

void ofxArtnetSender::setup(const string ipAddress, const int universe, const short port)
{
	this->universe = universe;
	udp.Create();
	udp.Connect(ipAddress.c_str(), port);
}


void ofxArtnetSender::threadedFunction()
{
	while (isThreadRunning())
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (_data != NULL)
			sendData((const unsigned char*)_data, _datasize);
		condition.wait(lock);
		ofSleepMillis(interval);
	}
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/

void ofxArtnetSender::sendArtnet(const ofPixels data)
{
	int datasize = data.size();
	sendArtnet(data.getData(), datasize);
}

void ofxArtnetSender::sendArtnet(const unsigned char* data, const int size)
{

	if (bThreadEnabled)
	{
		setData(data, size);
	}
	else
	{
		sendData(data, size);
	}
}


void ofxArtnetSender::sendData(const unsigned char* data, const int size)
{
	int datasize = size;
	vector<unsigned char> artnetBuff;
	allocateArtnetBuffer(artnetBuff, size);
	createProtocolHeader(artnetBuff);

	//universe
	artnetBuff[HEADER_LENGTH - 4] = (universe & 0xff);
	artnetBuff[HEADER_LENGTH - 3] = (universe >> 8);

	//datasize
	artnetBuff[HEADER_LENGTH - 2] = (datasize >> 8);
	artnetBuff[HEADER_LENGTH - 1] = (datasize & 0xff);

	memcpy(&artnetBuff[HEADER_LENGTH], data, size);

	udp.Send((const char *)artnetBuff.data(), artnetBuff.size());
}