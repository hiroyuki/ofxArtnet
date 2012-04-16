//
//  ofxArtnet.h
//  artnet
//
//  Created by 宏行 堀 on 12/01/10.
//  Copyright 2012年 rhizomatiks. All rights reserved.
//

#ifndef artnet_ofxArtnet_h
#define artnet_ofxArtnet_h
#include <artnet.h>
#include "ofMain.h"

typedef struct {
    int verbose;
    int help;
    char *ip_addr;
    int port_addr;
    int channel;
    int value;
    float fade_time;
} opts_t;


class ofxArtnet 
{
public:
    static int nodes_found;
    string SHORT_NAME;
    string LONG_NAME;
    
    ofxArtnet()
    {
        nodes_found = 0;
        SHORT_NAME = "ArtNet Node";
        LONG_NAME = "libartnet setdmx example";
    }
    
    void test();
    
    int do_fade(artnet_node node, opts_t *ops);
    
    
    //--------------------------------------------
    /*
     * Set our default options, command line args will overide this
     */
    void init_ops(opts_t *ops) {
        ops->verbose = 1;
        ops->help = 0;
        ops->ip_addr = "192.168.0.101";
        ops->port_addr = 0;
        ops->channel = 1;
        ops->value = 254;
        ops->fade_time = 2.0;
    }
    
    void display_help_and_exit(opts_t *ops) {
        printf(
               "Usage: --address <ip_address> --port <port_no> --channel <channel> --dmx <dmx_value> --fade <fade_time> \n"
               "\n"
               "Control lla port <-> universe mappings.\n"
               "\n"
               "  -a, --address <ip_address>      Address to send from.\n"
               "  -c, --channel <channel>         Channel to set (starts from 0).\n"
               "  -d, --dmx <value>               Value to set the channel to.\n"
               "  -h, --help                      Display this help message and exit.\n"
               "  -f, --fade <fade_time>          Total time of fade.\n"
               "  -p, --port <port_no>            Universe (port) address.\n"
               "  -v, --verbose                   Be verbose.\n"
               "\n" );
        exit(0);
    }
    
    private:
    int static reply_handler(artnet_node n, void *pp, void *d) {
        artnet_node_list nl = artnet_get_nl(n);
        
//        node nd = (node)n;
        
//        if (ofxArtnet::nodes_found == artnet_nl_get_length(nl)) {
//            // this is not a new node, just a previously discovered one sending
//            // another reply
//            return 0;
//        } else if(ofxArtnet::nodes_found == 0) {
//            // first node found
//            ofxArtnet::nodes_found++;
//            print_node_config(artnet_nl_first(nl));
//        } else {
//            // new node
//            ofxArtnet::nodes_found++;
//            print_node_config(artnet_nl_next(nl));
//        }
        return 0;
    }
    
    void static print_node_config(artnet_node_entry ne) {
        char ips[50] = "";
        sprintf(ips,"%d.%d.%d.%d", ne->ip[0], ne->ip[1], ne->ip[2], ne->ip[3]);
        printf("--------- %d.%d.%d.%d -------------\n", ne->ip[0], ne->ip[1], ne->ip[2], ne->ip[3]);
        printf("Short Name:   %s\n", ne->shortname);
        printf("Long Name:    %s\n", ne->longname);
        printf("Node Report:  %s\n", ne->nodereport);
        
        printf("Subnet:       0x%hhx\n", ne->sub);
        printf("Numb Ports:   %d\n", ne->numbports);
        printf("Input Addrs:  0x%hhx, 0x%hhx, 0x%hhx, 0x%hhx\n", ne->swin[0], ne->swin[1], ne->swin[2], ne->swin[3] );
        printf("Output Addrs: 0x%hhx, 0x%hhx, 0x%hhx, 0x%hhx\n", ne->swout[0], ne->swout[1], ne->swout[2], ne->swout[3] );
        printf("----------------------------------\n");
    }
};

#endif
