#include "ofxArtnetSender.h"



ofxArtnetSender::ofxArtnetSender()
{
}


ofxArtnetSender::~ofxArtnetSender()
{
}

void ofxArtnetSender::setup(const string ipAddress, const short port)
{
	udp.Create();
	udp.Connect(ipAddress.c_str(), port);
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/

void ofxArtnetSender::sendArtnet(const ofPixels data, const int universe)
{
	int datasize = data.size();
	vector<unsigned char> artnetBuff;
	
	createProtocolHeader(artnetBuff);

	//universe
	artnetBuff.push_back(universe & 0xff);
	artnetBuff.push_back(universe >> 8);

	//datasize
	artnetBuff.push_back(datasize >> 8);
	artnetBuff.push_back(datasize & 0xff);

	for (int i = 0; i < datasize; i++)
	{
		artnetBuff.push_back(data.getData()[i]);
	}
	udp.Send((const char *)artnetBuff.data(), artnetBuff.size());
}

void ofxArtnetSender::sendArtnet(const unsigned char* data, const int size, const int universe)
{
	int datasize = size;
	vector<unsigned char> artnetBuff;
	createProtocolHeader(artnetBuff);

	//universe
	artnetBuff.push_back(universe & 0xff);
	artnetBuff.push_back(universe >> 8);

	//datasize
	artnetBuff.push_back(datasize >> 8);
	artnetBuff.push_back(datasize & 0xff);



	for (int i = 0; i < datasize; i++)
	{
		artnetBuff.push_back(data.getData()[i]);
	}
	udp.Send((const char *)artnetBuff.data(), artnetBuff.size());
}