#include "ofxArtnetProtocol.h"



ofxArtnetProtocol::ofxArtnetProtocol()
{
}


ofxArtnetProtocol::~ofxArtnetProtocol()
{
}


void ofxArtnetProtocol::allocateArtnetBuffer(std::vector<unsigned char>& buff, unsigned int size)
{	
	size = HEADER_LENGTH + size;
	buff.resize(size);
}

//ref protocols
//https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/
void ofxArtnetProtocol::createProtocolHeader(std::vector<unsigned char>& buf, unsigned char seq)
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
	buf[size + 2] = (OP_OUTPUT >> 8) & 0xff;

	buf[size + 3] = 0;//protocol version high byte
	buf[size + 4] = 14;//protocol version low byte

	buf[size + 5] = seq;//sequence no - disable sequence(0)

	buf[size + 6] = 0;//The physical input port from which DMX512 - information only
}
