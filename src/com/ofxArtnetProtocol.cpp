#include "ofxArtnetProtocol.h"



ofxArtnetProtocol::ofxArtnetProtocol()
{
}


ofxArtnetProtocol::~ofxArtnetProtocol()
{
}


void ofxArtnetProtocol::allocateArtnetBuffer(vector<unsigned char>& buff, unsigned int size)
{	
	size = HEADER_LENGTH + size;
	buff.resize(size);
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/
void ofxArtnetProtocol::createProtocolHeader(vector<unsigned char>& buf)
{
	if (buf.size() < HEAD.length() + 6)
	{
		ofLogError() << "allocate vector for art-net before creation of header";
	}
	int size = HEAD.length();
	for (int i = 0; i < HEAD.length(); i++)
	{
		buf[i] = HEAD[i];
	}
	buf[size] = 0;//end string
	buf[size + 1] = (OP_OUTPUT & 0xff);
	buf[size + 2] = (OP_OUTPUT >> 8);

	buf[size + 3] = 0;//protocol version high byte
	buf[size + 4] = 14;//protocol version low byte

	buf[size + 5] = 0;//sequence no - disable sequence(0)

	buf[size + 6] = 0;//The physical input port from which DMX512 - information only
}