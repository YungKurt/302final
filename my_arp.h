/**
 * NWEN 302 ARP Implementation (Header File)
 * You can edit this file to define your custom data structures and function
 * prototypes. But DO NOT change the prototypes of the given functions
 *      my_arp_init
 *      my_arp_resolve
 *      my_arp_handle_request
 *      my_arp_handle_reply
 */

#ifndef __MY_ARP_H__
#define __MY_ARP_H__

#include <stdint.h>
#include <netinet/in.h>


/**
 * This is a function that you should implement in my_arp.c
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
void my_arp_init();

/**
 * This is a function that you should implement in my_arp.c
 * The purpose of this function is to initiate ARP request. This function
 * is called whenever a node has a datagram to be sent to @ip_address and
 * it has no MAC address of this node.
 * 
 * @param ip_address IPv4 address to be resolved
 */ 
void my_arp_resolve (uint32_t ip_address);

/**
 * This is a function that you should implement in my_arp.c
 * The purpose of this function is to handle ARP request. This function
 * is called whenever a node receives an ARP request.
 * 
 * @param ip_address IPv4 address to be resolved
 * @param src_mac_address Source MAC address. This should be a 48-bit MAC address.
 */ 
void my_arp_handle_request(uint32_t ip_address, const unsigned char *mac_address);

/**
 * This is a function that you should implement in my_arp.c
 * The purpose of this function is to handle ARP reply. This function
 * is called whenever a node receives an ARP reply.
 * 
 * @param ip_address IPv4 address to be resolved
 * @param mac_address MAC address of the interface with @ip_address.
 * This should be a 48-bit MAC address.
 */ 
void my_arp_handle_reply(uint32_t ip_address, const unsigned char *mac_address);

/**
 * This is a function that you should implement in my_arp.c
 * This function is called whenever a frame is transmitted to a node with
 * IP address @ip_address and MAC address @mac_address
 * 
 * @param ip_address IPv4 address
 * @param mac_address MAC address of the interface with @ip_address.
 */ 
void my_arp_frame_transmitted(uint32_t ip_address, const unsigned char *mac_address);


#endif /* __MY_ARP_H__ */
