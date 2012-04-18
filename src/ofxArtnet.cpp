//
//  ofxArtnet.cpp
//  artnet
//
//  Created by 宏行 堀 on 12/01/10.
//  Copyright 2012年 rhizomatiks. All rights reserved.
//
#include "ofxArtnet.h"

int ofxArtnet::nodes_found;
status_artnet ofxArtnet::status;


void ofxArtnet::setup(const char* interfaceIP, int port_addr, int verbose)
{
    nodes_found = 0;

    // create new artnet node, and set config values
    
    if ( (node = artnet_new(interfaceIP, verbose)) == NULL) 
    {
        printf("cannot create node: %s\n", artnet_strerror() );
        goto error_destroy;            
    }
    artnet_set_short_name(node, SHORT_NAME.c_str());
    artnet_set_long_name(node, LONG_NAME.c_str());
    artnet_set_node_type(node, ARTNET_RAW);
    
    artnet_set_port_type(node, 0, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX);
    artnet_set_port_addr(node, 0, ARTNET_INPUT_PORT, port_addr);
    artnet_set_handler(node, ARTNET_REPLY_HANDLER, ofxArtnet::reply_handler, NULL);
    
    if (artnet_start(node) != ARTNET_EOK) {
        printf("Failed to start: %s\n", artnet_strerror() );
        goto error_destroy;
    }
    
    sd = artnet_get_sd(node);
    
    find_timeout = ofGetElapsedTimeMillis();
    status = NODES_FINDING;
	if (artnet_send_poll(node, NULL, ARTNET_TTM_DEFAULT) != ARTNET_EOK) {
        printf("send poll failed: %s\n", artnet_strerror() );
        goto error_destroy;
	}
    startThread(true, false);
    return;
    
    error_destroy :
    artnet_destroy(node);
    
//    free(ops.ip_addr);
    exit(1);
}

void ofxArtnet::threadedFunction(){
    int maxsd;
    fd_set rset;
	struct timeval tv;
    while(isThreadRunning()) {
         switch (status) {
             case NODES_FINDING:
                 while (ofGetElapsedTimeMillis() - find_timeout < _TIMEOUT) {    
                     FD_ZERO(&rset);
                     FD_SET(sd, &rset);
                     tv.tv_usec = 0;
                     tv.tv_sec = _TIMEOUT / 1000.f;
                     maxsd = sd;
                     
                     switch (select(maxsd+1, &rset, NULL, NULL, &tv)) {
                         case 0:
                             // timeout
                             break;
                         case -1:
                             printf("select error\n");
                             break;
                         default:
                             artnet_read(node,0);
                             break;
                     }
                 }
                 if ( nodes_found > 0) status = NODES_FOUND;
                 else status = NOT_READY;
                 stopThread();
                 break;
                 
             default:
                 break;
         }
     }
}

void ofxArtnet::sendDmx( string targetIp, const unsigned char* data512, int size )
{
    
    if ( status == NODES_FOUND)
    {
        if ( artnet_send_dmx(node, 0, targetIp.c_str(), size , data512) != ARTNET_EOK) {
            printf("Failed to Send: %s\n", artnet_strerror() );
        }
    }
}