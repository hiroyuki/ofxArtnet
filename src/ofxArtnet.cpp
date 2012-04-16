//
//  ofxArtnet.cpp
//  artnet
//
//  Created by 宏行 堀 on 12/01/10.
//  Copyright 2012年 rhizomatiks. All rights reserved.
//
#include "ofxArtnet.h"

int ofxArtnet::nodes_found;


void ofxArtnet::test()
{
    nodes_found = 0;
    opts_t ops;
    artnet_node node;
    
    // init and parse the args
    init_ops(&ops);
//    parse_args(&ops, argc, argv);
    
    // do some checks
    if (ops.help)
        display_help_and_exit(&ops);
    
    if (ops.channel < 1 || ops.channel > 512)
        display_help_and_exit(&ops);
    
    if (ops.value < 0 || ops.value > 255)
        display_help_and_exit(&ops);
    
    if (ops.port_addr < 0 || ops.port_addr > 4)
        display_help_and_exit(&ops);
    // create new artnet node, and set config values
    
    if ( (node = artnet_new(ops.ip_addr, ops.verbose)) == NULL) 
    {
        printf("cannot create node: %s\n", artnet_strerror() );
        goto error_destroy;            
    }
    artnet_set_short_name(node, SHORT_NAME.c_str());
    artnet_set_long_name(node, LONG_NAME.c_str());
    artnet_set_node_type(node, ARTNET_RAW);
    
    artnet_set_port_type(node, 0, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX);
    artnet_set_port_addr(node, 0, ARTNET_INPUT_PORT, ops.port_addr);
    artnet_set_handler(node, ARTNET_REPLY_HANDLER, ofxArtnet::reply_handler, NULL);
    
    if (artnet_start(node) != ARTNET_EOK) {
        printf("Failed to start: %s\n", artnet_strerror() );
        goto error_destroy;
    }
    
    printf("channel is %i\n", ops.channel);
    do_fade(node, &ops);
    
    return;
    
    error_destroy :
    artnet_destroy(node);
    
//    free(ops.ip_addr);
    exit(1);
}

/*
 *
 *
 */
int ofxArtnet::do_fade(artnet_node node, opts_t *ops) {
    int chan = ops->channel;
    float fadetime = ops->fade_time;
    int val = ops->value;
    uint8_t dmx[chan];
    float p;
    
    memset(dmx, 0x00, chan);
    
    chan--;
    
    artnet_send_dmx(node, 0, chan, dmx);
//    msleep(40);
    
    const unsigned long tstart=ofGetElapsedTimeMillis();
    const unsigned long tend=tstart+(int)(fadetime*1000.0);
    unsigned long t=tstart;
    
    while (t<=tend) {
        t=ofGetElapsedTimeMillis();
        
        if (fadetime)
            p = (float)(t-tstart)/1000.0f/fadetime;
        else
            p = 1.0;
        
        dmx[chan]=(int)(float)val*p;
        
//        msleep(40);
        //  printf("%f %i %i %f %li\n", p, chan, dmx[chan] , fadetime, t-tstart);
        
        // we have to call raw_send here as it sends a sequence number of 0
        // otherwise each execution of artnet_setdmx starts the sequence from 0
        // which confuses some devices
        if (artnet_raw_send_dmx(node, ops->port_addr , chan+1, dmx)) {
            printf("failed to send: %s\n", artnet_strerror() );
        }
        
        t=ofGetElapsedTimeMillis(); // get current time, because the last time is too old (due to the sleep)
    }
    
    return 0;
}