#include "ofxArtnet.h"

ofxArtnet::ofxArtnet()
{
}


ofxArtnet::~ofxArtnet()
{
}

void ofxArtnet::setup(const string ipAddress, const short port)
{
	udp.Create();
	udp.Connect(ipAddress.c_str(), port);
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/

void ofxArtnet::sendArtnet(const ofPixels data, const int universe)
{
	int datasize = data.size();
	vector<unsigned char> artnetBuff;
	for (int i = 0; i < HEAD.length(); i++)
	{
		artnetBuff.push_back(HEAD[i]);
	}
	artnetBuff.push_back(0);//end string
	artnetBuff.push_back(OP_OUTPUT & 0xff);
	artnetBuff.push_back(OP_OUTPUT >> 8);
	
	artnetBuff.push_back(0);//protocol version high byte
	artnetBuff.push_back(14);//protocol version low byte

	artnetBuff.push_back(0);//sequence no - disable sequence(0)
	artnetBuff.push_back(0);//The physical input port from which DMX512

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
