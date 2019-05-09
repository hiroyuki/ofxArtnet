#pragma once
#include "ofMain.h"

class ofxArtnetMessage
{
public:
	friend class ofxArtnetSender;
	friend class ofxArtnetReceiver;
	ofxArtnetMessage();
	ofxArtnetMessage(const ofPixels& pix);
	~ofxArtnetMessage();
	ofxArtnetMessage(const ofxArtnetMessage& origin);
    ofxArtnetMessage(ofxArtnetMessage&& origin);

	void allocate(size_t size);
	void clear();
    
	void setData(const unsigned char* data, size_t size);
	void setData(ofIndexType index, unsigned char data);
	void setData(const ofPixels& pix);
    void setData(std::vector<uint8_t> &data);

	void readTo(unsigned char* data);
    void readTo(std::vector<uint8_t> &data);

	inline void setUniverse15(unsigned int universe) { _portAddress = _universe = universe; }
	inline void setUniverse(unsigned int net, unsigned int subnet, unsigned int universe)
	{
		_net = net;
		_subnet = subnet;
		_universe = universe;
		_portAddress = (_net << 8) + (_subnet << 4) + _universe;
	}
	inline unsigned int getUniverse() const { return _universe; }
	inline unsigned int getSubnet() const { return _subnet; }
	inline unsigned int getNet() const { return _net; }
	inline unsigned int getSize() const { return _data.size(); }
	ofxArtnetMessage& operator = (const ofxArtnetMessage& obj);
private:
	inline unsigned int getPortAddess() const { return _portAddress; }
	inline unsigned char getSequence() const { return _seqNo; }
	unsigned int _universe, _subnet, _net;
    std::vector<uint8_t> _data;
	unsigned int _portAddress;
	unsigned char _seqNo;
};

