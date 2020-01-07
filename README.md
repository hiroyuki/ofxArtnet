# ofxArtnet

[![Join the chat at https://gitter.im/hiroyuki/ofxArtnet](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/hiroyuki/ofxArtnet?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


**openframeworks** addon of artnet

This addon is comletely different from the old version which uses libartnet.  
In case you still need the old version, please checkout the *legacy* branch.

## Overview

ofxArtnet works by sending ofPixels through to ArtNet to fixtures.

### Initialize an FBO and ArtNet Sender
```C++
ofFbo sendData;
ofxArtnetSender artnet;
```

### Allocate the frame buffer and ArtNet sender


```C++
string targetIp = "127.0.0.1";
int width = 170;
int height = 1;
int internalformat = GL_RGB;
sendData.allocate(width, height, internalformat);
artnet.setup(targetIP);
```

### Draw to the frame buffer and send to artnet
```C++
ofColor = 
sendData.begin();
  ofClear(0);
  ofSetColor(color);
  ofDrawRectangle(0, 0, sendData.getWidth(), 1);
sendData.end();

// Convert the frame buffer to ofPixels
ofPixels data;
sendData.readToPixels(data);

// Send the pixel data over Artnet
artnet.sendArtnet(data);
```

## Dependencies
[ofxNetwork](https://openframeworks.cc/documentation/ofxNetwork/)
