#include "ofxArtnetSender.h"



ofxArtnetSender::ofxArtnetSender()
{
}

ofxArtnetSender::ofxArtnetSender(const ofxArtnetSender& origin)
{
	udp.Create();
	udp.Connect(targetIp.c_str(), targetPort);
}


ofxArtnetSender::~ofxArtnetSender()
{
	if (isThreadRunning())
	{
		waitForThread(true);
	}
	udp.Close();
	_messages.clear();

}

void ofxArtnetSender::setup(const std::string& ipAddress, const uint16_t port)
{
	this->targetIp = ipAddress;
	this->targetPort = port;
	udp.Create();
	udp.Connect(ipAddress.c_str(), port);
}


void ofxArtnetSender::threadedFunction()
{
	while (isThreadRunning())
	{
		ofSleepMillis(interval);
		std::unique_lock<std::mutex> lock(mutex);
		for(auto& m : _messages) sendData(m);
		_messages.clear();
	}
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/


void ofxArtnetSender::sendArtnet(const ofxArtnetMessage& message)
{
	if (bThreadEnabled)
	{
		std::unique_lock<std::mutex> lock(mutex);
		_messages.push_back( message );
	}
	else
	{
		//_data‚ğì¬‚µ‚Äsend
		sendData(message);
	}
}

void ofxArtnetSender::createBuffer(const ofxArtnetMessage& message, std::vector<unsigned char>& data)
{
	int datasize = message.getSize();
	allocateArtnetBuffer(data, datasize);
	createProtocolHeader(data, message.getSequence());
	//universe
	data[HEADER_LENGTH - 4] = (message.getPortAddess() & 0xff);
	data[HEADER_LENGTH - 3] = (message.getPortAddess() >> 8);

	//datasize
	data[HEADER_LENGTH - 2] = (datasize >> 8);
	data[HEADER_LENGTH - 1] = (datasize & 0xff);
	memcpy(&data[HEADER_LENGTH], message._data.data(), message.getSize());
}

void ofxArtnetSender::sendData(const ofxArtnetMessage& message)
{
	int datasize = message.getSize();
	if (datasize > 0)
	{
		std::vector<unsigned char> artnetBuff;
		createBuffer(message, artnetBuff);
		udp.Send((const char *)artnetBuff.data(), artnetBuff.size());
	}
}
