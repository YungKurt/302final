/**
 * NWEN 302 Learning Switch Implementation (Header File)
 * You can edit this file to define your custom data structures and function
 * prototypes. But DO NOT change the prototypes of the given functions
 *      my_lswitch_init
 *      my_lswitch_frame_receive
 */

#ifndef __MY_LSWITCH_H__
#define __MY_LSWITCH_H__


/**
 * This is a function that you should implement in my_lswitch.c
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
void my_lswitch_init();


/**
 * This is a function that you should implement in my_lswitch.c
 * This function is called whenever a frame is received by the switch.
 * 
 * @param source_mac_address Source MAC address of the frame.
 * @param dest_mac_address Destination MAC address of the frame.
 * @param device Name of interface where the frame was received.
 */ 
void my_lswitch_frame_receive(const unsigned char *source_mac_address, 
    const unsigned char *dest_mac_address, const char *device);

void sig_handler(int signum);

void add_entry(struct entry* new_entry);

void delete_entry(struct entry** head, const unsigned char mac);


#endif /* __MY_LSWITCH_H__ */
