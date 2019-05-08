#include "ofxArtnetMessage.h"

ofxArtnetMessage::ofxArtnetMessage():_data(nullptr)
{
}

ofxArtnetMessage::ofxArtnetMessage(const ofPixels& pix) : _data(nullptr), _size(0), _universe(0), _subnet(0), _net(0), _portAddress(0)
{
	setData(pix);
}


ofxArtnetMessage::~ofxArtnetMessage()
{
	clear();
}

ofxArtnetMessage::ofxArtnetMessage(const ofxArtnetMessage& origin) : _data(nullptr), _size(0), _universe(0), _subnet(0), _net(0), _portAddress(0)
{
	if (origin._data != nullptr)
	{
		_data = new unsigned char[origin._size];
		memcpy(_data, origin._data, origin._size);
		this->_size = origin._size;
	}
	this->_universe = origin._universe;
	this->_subnet = origin._subnet;
	this->_net = origin._net;
	this->_portAddress = origin._portAddress;
}

ofxArtnetMessage& ofxArtnetMessage::operator = (const ofxArtnetMessage& origin)
{
	this->_size = 0;
	if (origin._data != nullptr)
	{
		_data = new unsigned char[origin._size];
		memcpy(_data, origin._data, origin._size);
		this->_size = origin._size;
	}
	this->_universe = origin._universe;
	this->_subnet = origin._subnet;
	this->_net = origin._net;
	this->_portAddress = origin._portAddress;
	return *this;
}


void ofxArtnetMessage::allocate(unsigned int size)
{
	_data = new unsigned char[size];
	_size = size;
}



void ofxArtnetMessage::readTo(unsigned char* data)
{
	memcpy(data, _data, _size);
}

void ofxArtnetMessage::clear()
{
	if (_data != nullptr)
	{
		delete[] _data;
		_data = nullptr;
	}
}

void ofxArtnetMessage::setData(const ofPixels& pix)
{
	int datasize = pix.size();
	setData(pix.getData(), datasize);
}

void ofxArtnetMessage::setData(ofIndexType index, unsigned char& data)
{
	if (_data == nullptr || _size < index + 1)
	{
		ofLogWarning() << "data size is not big enouth";
		return;
	}
	_data[index] = data;
}

void ofxArtnetMessage::setData(const unsigned char* data, const int size)
{
	std::unique_lock<std::mutex> lock(mutex);
	if (_data == nullptr)
	{
		_data = new unsigned char[size];
	}
	memcpy(_data, data, size);
	_size = size;
	_seqNo++;
	_seqNo %= 256;
}
