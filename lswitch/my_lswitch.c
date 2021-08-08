/**
 * NWEN 302 ARP Implementation
 * This is where you should implement the functions
 *
 * Name:
 * Student ID:
 */ 

#include "lswitch_functions.h"
#include "my_lswitch.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/**
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
void my_lswitch_init()
{
}

/**
 * This is a function that you should implement in my_lswitch.c
 * This function is called whenever a frame is received by the switch.
 * 
 * @param source_mac_address Source MAC address of the frame.
 * @param dest_mac_address Destination MAC address of the frame.
 * @param device Name of interface where the frame was received.
 */ 
void my_lswitch_frame_receive(const unsigned char *source_mac_address, 
    const unsigned char *dest_mac_address, const char *device)
{
}



