/**
 * NWEN 302 ARP Implementation
 * This is where you should implement the functions
 *
 * Name: Kurtis Fenton
 * Student ID: 300473865
 */ 

#include "lswitch_functions.h"
#include "my_lswitch.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

struct entry {
    unsigned char mac_address;
	char device;
	int age;
    struct entry *next;
};
struct entry* head = NULL;
/**
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
bool find_entry(struct entry* head_ref, unsigned char mac)
{
	struct entry* current = head_ref;
	while(current != NULL){
		if(current->mac_address == mac){
			current->age = 30;
			return true;		
		}
		current = current->next;
	}
	return false;
}

void my_lswitch_init()
{
	signal(SIGALRM, sig_handler);
	alarm(1);	
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
	/* create a new entry in the linked list and switch table*/
	if(find_entry(head, source_mac_address)){
		printf("Entry exists, refreshed ageing value.\n");
		return;
	}
	add_entry(&head, source_mac_address, device);
	lswitch_insert_table(source_mac_address, device);
	printf("Adding entry to table...\n");
	printf("MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", source_mac_address[0], 
	source_mac_address[1], source_mac_address[2], source_mac_address[3], 
	source_mac_address[4], source_mac_address[5]);
}

/* function called when alarm goes off, remove expired entry from switch table */
void sig_handler(int signum)
{
	struct entry* e = head;
	while(e != NULL){
		e->age = e->age - 1;
		/*remove expired entry */		
		if(e->age <= 0){
			const unsigned char *mac = e->mac_address;
			const char *dev = e->device;
			printf("Deleting entry from table...\n");
			printf("MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", mac[0], mac[1],
			mac[2], mac[3], mac[4], mac[5]);
			lswitch_delete_table(mac, dev);
			delete_entry(e->mac_address);			
		}
		e = e->next;
	}
	alarm(1);			

}

/* traverse to the end of the linked list and adds the new entry */
add_entry(struct entry** head, const unsigned char mac, const char *dev)
{
	struct entry* new_entry = (struct entry*)malloc(sizeof(struct entry));
	new_entry->mac_address = mac;
	new_entry->device = dev;
	new_entry->age = 30;
	new_entry->next = (*head);
	(*head) = new_entry;
}

/* deletes entry from linked list */
delete_entry(const unsigned char mac)
{
	struct entry *temp = head; 
	struct entry *prev;

	int ret = memcmp(temp->mac_address, mac,6);
	//head itself to be deleted
	if(temp != NULL && ret == 0){
		head = temp->next;
		free(temp);
		return;
	}
	//search for entry to delete
	while(temp != NULL && memcmp(temp->mac_address, mac,6)!= 0){
		prev = temp;
		temp = temp->next;	
	}
	if(temp == NULL){
		return;
	}
	//unlink node from list
	prev->next = temp->next;
	free(temp);
}


