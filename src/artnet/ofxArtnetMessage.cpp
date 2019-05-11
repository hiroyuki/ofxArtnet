#include "ofxArtnetMessage.h"

ofxArtnetMessage::ofxArtnetMessage() : _data(), _universe(0), _subnet(0), _net(0), _portAddress(0)
{
}

ofxArtnetMessage::ofxArtnetMessage(const ofPixels& pix) : _data(), _universe(0), _subnet(0), _net(0), _portAddress(0)
{
	setData(pix);
}


ofxArtnetMessage::~ofxArtnetMessage()
{
	clear();
}

ofxArtnetMessage::ofxArtnetMessage(const ofxArtnetMessage& origin)
: _data(origin._data)
, _universe(origin._universe)
, _subnet(origin._subnet)
, _net(origin._net)
, _portAddress(origin._portAddress)
{}

ofxArtnetMessage::ofxArtnetMessage(ofxArtnetMessage&& origin)
: _data(std::move(origin._data))
, _universe(origin._universe)
, _subnet(origin._subnet)
, _net(origin._net)
, _portAddress(origin._portAddress)
{}

ofxArtnetMessage& ofxArtnetMessage::operator = (const ofxArtnetMessage& origin)
{
    _data = origin._data;
	this->_universe = origin._universe;
	this->_subnet = origin._subnet;
	this->_net = origin._net;
	this->_portAddress = origin._portAddress;
	return *this;
}


void ofxArtnetMessage::allocate(size_t size)
{
    _data.resize(size);
}

void ofxArtnetMessage::readTo(unsigned char* data)
{
	memcpy(data, _data.data(), _data.size());
}

void ofxArtnetMessage::readTo(std::vector<uint8_t> &data)
{
    data = _data;
}

void ofxArtnetMessage::clear()
{
    _data.clear();
}

void ofxArtnetMessage::setData(const ofPixels& pix)
{
	int datasize = pix.size();
	setData(pix.getData(), datasize);
}

void ofxArtnetMessage::setData(std::vector<uint8_t> &data) {
    _data = data;
}

void ofxArtnetMessage::setData(ofIndexType index, unsigned char data)
{
	if (getSize() <= index) {
		ofLogWarning() << "data size is not big enouth";
		return;
	}
	_data[index] = data;
}

void ofxArtnetMessage::setData(const unsigned char* data, size_t size)
{
    _data.resize(size);
	memcpy(_data.data(), data, size);
	_seqNo++;
	_seqNo %= 256;
}
