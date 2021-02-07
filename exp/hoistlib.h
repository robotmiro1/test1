#ifndef _HOISTLIB_H_
#define _HOISTLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#define MAX_HEIGHT 200
#define MIN_HEIGHT 0
#define STEP 5 // the hoist speed is 5 cm/s

// Server - Reader message structure
typedef struct message* msg_t;

// Hoist statuses
enum status {STOP = 'S', UP = 'U', DOWN = 'D', EXIT = 'E', TOP = 'T', BOTTOM = 'B'};

// ------------- Utility functions ------------------
/*
	Throw error.
	
	arguments:
		msg - error message
		ret - exit status
*/
void error(char *msg, int ret);

/*
	Spawn a child process.
	arguments:
		ex_name - path to the process executable
		fd_log - log file descriptor
		fd_in - input file descriptor (might be socket or pipe)
		fd_out - output file descriptor (might be socket or pipe)
		new_shell - whether the child process should run in a new shell
	return:
		child_pid - PID of the children, from inside the father. The functions
					should not return from inside the spawned children
*/
int spawn(char *ex_name, int fd_log, int *fd_in, int *fd_out, char new_shell);

// -------------- Height manipulation functions -------------------------------
/*
	Try to increase the hoist height
	
	If height >= maximum height, set it to maximum height, otherwise increase by STEP.
	
	arguments:
		*height - pointer to the hoist height variable
*/

void height_tryup  	(int *height);
/*
	Try to decrease the hoist height
	
	If height <= minimum height, set it to minimum height, otherwise decrease by STEP.
	
	arguments:
		*height - pointer to the hoist height variable
*/
void height_trydown	(int *height);

// -------------- Message manipulation functions -------------------------------
/* 
	Set the message height field
	arguments:
		p_msg - pointer to the message structure
		height - hoist height variable
		status - status to be assigned
*/
void msg_setheight	(msg_t p_msg, int height);

/*
	Set the message status field
	arguments:
		p_msg - pointer to the message structure
		status - status to be assigned
*/
void msg_setstatus	(msg_t p_msg, char status);

/*
	Get the message height field
	arguments:
		p_msg - pointer to the message structure
	return:
		msg_height - height field in the message
*/
int  msg_getheight	(msg_t p_msg);

/*
	Get the message status field
	arguments:
		p_msg - pointer to the message structure
	return:
		msg_status - status field in the message
*/
char msg_getstatus	(msg_t p_msg);

/*
	Get the message size
	arguments:
		p_msg - pointer to the message structure
	return:
		size - size of the message structure
*/
int  msg_getsize	();

/*
	Initialize the message structure
	
	Dynamically allocate memory for a message structure, initialize its
	fields to {height = 0, status = BOTTOM}
	
	arguments:
		pp_msg - double pointer to the message structure
*/
void msg_init		(msg_t *pp_msg);

/*
	Free the memory occupated by the message
	arguments:
		p_msg - pointer to the dynamic message structure to free
*/
void msg_free		(msg_t p_msg);
#endif
