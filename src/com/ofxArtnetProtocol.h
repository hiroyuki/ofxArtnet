#pragma once
#include "ofMain.h"
#include "ofxNetwork.h"

class ofxArtnetProtocol
{
	public:
		ofxArtnetProtocol();
		~ofxArtnetProtocol();

		void allocateArtnetBuffer(vector<unsigned char>& buff, unsigned int size);
		void createProtocolHeader(vector<unsigned char>& buff);

	protected:
		ofxUDPManager udp;
		const string HEAD = "Art-Net";
		const int HEADER_LENGTH = 18;
		const short OP_OUTPUT = 0x5000;
};
