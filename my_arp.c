/**
 * NWEN 302 ARP Implementation
 * This is where you should implement the functions
 *
 * Name:Kurtis Fenton
 * Student ID:300473865
 */ 

#include "arp_functions.h"
#include "my_arp.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>

/*mac address*/
unsigned char my_mac_address[6];
/* IP address*/
uint32_t my_ip_address;

/**
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
void my_arp_init()
{
	printf("init started.\n");
	
}

/**
 * The purpose of this function is to initiate ARP request. This function
 * is called whenever a node has a datagram to be sent to @ip_address and
 * it has no MAC address of this node.
 * 
 * @param ip_address IPv4 address to be resolved
 */ 
void my_arp_resolve (uint32_t ip_address)
{
	printf("arp resolve function.\n");
	char dest_mac_address[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};	
	printf("Sending broadcast request.\n");
	arp_send_query(ip_address, dest_mac_address);
}

/**
 * This is a function that you should implement in my_arp.c
 * The purpose of this function is to handle ARP request. This function
 * is called whenever a node receives an ARP request.
 * Hint: This function should create an Ethernet frame containing the ARP reply.
 * See the Implementation of arp_send_query() in arp_functions.c to get an idea
 * of how to construct a raw Ethernet frame.
 * 
 * @param ip_address IPv4 address to be resolved
 * @param src_mac_address Source MAC address. This should be a 48-bit MAC address.
 */ 
void my_arp_handle_request(uint32_t ip_address, const unsigned char *mac_address)
{
	printf("Handle request function.\n");
	unsigned char mac_buffer[6];
	arp_get_my_macaddr(mac_buffer);
	int my_ip_address = arp_get_my_ipaddr();

	if(my_ip_address == ip_address){
		
		char buffer[1000] = {};	

		/* eth header */
		printf("Constructing eth header.\n");
		struct ethhdr *eth = (struct ethhdr *)buffer;
		memcpy(eth->h_source, mac_buffer, 6);
		memcpy(eth->h_dest, mac_address, 6);
		eth->h_proto = htons(ETH_P_ARP);

		/* arp header */
		printf("Constructing arp header.\n");
		struct arphdr *arph = (struct arphdr*)(buffer + sizeof(struct ethhdr));
		arph->ar_hrd = htons(ARPHRD_ETHER); 
		arph->ar_pro = htons(ETH_P_IP);
		arph->ar_hln = 6;
		arph->ar_pln = 4;
		arph->ar_op = htons(ARPOP_REPLY);

		/* Fill in rest of the contents */
		printf("Filling in arpdata.\n");
		struct arpdata *arpd = (struct arpdata*)(buffer + sizeof(struct ethhdr) + sizeof(struct arphdr));
		memcpy(arpd->ar_sha, mac_buffer, 6); /*source mac */
		memcpy(arpd->ar_tha, mac_address, 6); /* target mac */
		arpd->ar_sip = htonl(my_ip_address); /*src ip */
		arpd->ar_tip = htonl(ip_address); /* target ip */

		printf("Sending ethernet arp frame.\n");
		int len = sizeof(struct ethhdr) + sizeof(struct arphdr) + sizeof(struct arpdata);
		arp_send_reply(buffer, len);
		printf("Sent.\n");

	}

	 
	
}

/**
 * The purpose of this function is to handle ARP reply. This function
 * is called whenever a node receives an ARP reply.
 * Hint: Use this function to trigger the insertion of an appropriate entry
 * in the ARP cache.
 * 
 * @param ip_address IPv4 address to be resolved
 * @param mac_address MAC address of the interface with @ip_address.
 * This should be a 48-bit MAC address.
 */ 
void my_arp_handle_reply(uint32_t ip_address, const unsigned char *mac_address)
{
	arp_insert_cache(ip_address, mac_address);	   
}

/**
 * This function is called whenever a frame is transmitted to a node with
 * IP address @ip_address and MAC address @mac_address
 * 
 * @param ip_address IPv4 address
 * @param mac_address MAC address of the interface with @ip_address.
 */ 
void my_arp_frame_transmitted(uint32_t ip_address, const unsigned char *mac_address)
{
}



