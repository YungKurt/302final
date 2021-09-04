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

struct entry {
    const unsigned char mac_address;
	const char device;
	int age;
    struct entry *next;
};
struct entry* head = NULL;
/**
 * This function will be called at the start of the program. You can
 * use this function to initialize your own data structures, setup timers,
 * or do any stuff to initialize your code.
 */
void my_lswitch_init()
{
	head = (struct entry*)malloc(sizeof(struct entry));	
	head->next = NULL;
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
	/* create a new entry in the linked list */
	struct entry* new_entry = NULL;
	new_entry = (struct entry*)malloc(sizeof(struct entry));	
	new_entry->mac_address = source_mac_address;
	new_entry->device = device;
	new_entry->age = 30;
	add_entry(new_entry);
	lswitch_insert_table(source_mac_address, device);
	/* set alarm for 30 seconds, (ageing timer) */ 
}

/* function called when alarm goes off, remove expired entry from switch table */
void sig_handler(int signum)
{
	struct entry* e = head;
	while(e != NULL){
		e->age = e->age - 1;
		/*remove expired entry */		
		if(e->age <= 0){
			lswitch_delete_table(e->mac_address, e->device);
			delete_entry(&head, e->mac_address)			
		}
		e = e->next;
	}
	alarm(0.98);			

}

/* traverse to the end of the linked list and adds the new entry */
void add_entry(struct entry* new_entry)
{
	struct entry* e = head;
	while(e != NULL){
		if(e->next == NULL){
			e->next = new_entry;		
			return;		
		}
		e = e->next;
	}
}

/* deletes entry from linked list */
void delete_entry(struct entry** head, const unsigned char mac)
{
	struct entry *temp = *head, *prev;
	//head itself to be deleted
	if(temp != NULL && temp->mac_address == mac){
		*head = temp->next;
		free(temp);
		return;
	}
	//search for entry to delete
	while(temp != NULL && temp->mac_address != mac){
		prev = temp;
		temp = temp->next;	
	}
	//unlink node from list
	prev->next = temp->next;
	free(temp);
}

