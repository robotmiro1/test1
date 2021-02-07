#include "hoistlib.h"

/*
	NOTE_1
	The log file is opened from the file descriptor passed from the master process, in order to avoid problem with 
	multiple processes trying to append to it
*/

int main(int argc, char * argv[])
{
	const char *NAME = "READER"; //process name for the log file
	int ret; //for storing return values
	int sockfd;
	char buffer[25]; //for printing hoist status
	msg_t msg; //message received from the server
	int msg_size;

	FILE *log;
	int fd_log;

	//check number of arguments provided
	if (argc<3){
		fprintf(stderr,"READER: too few arguments passed\n");
		exit(1);
	}

	//open the log file
	fd_log = atoi(argv[1]);
	if((log = fdopen(fd_log, "w"))==(FILE*)NULL){
		perror("READER: Log file open from filedes");
	}
	sockfd = atoi(argv[2]);
	
	msg_init(&msg); msg_size = msg_getsize(); // initialize message pointed to by msg

	fprintf(log, "%s: starting\n", NAME); fflush(log);
	
	//until the EXIT command is received from the server
	while (msg_getstatus(msg) != EXIT)
	{
		//clear the buffer
		bzero(buffer, 25);
		//read the message from the server
		if ((ret = read(sockfd, msg, msg_size)) < 0)
			error("READER: reading from socket", ret);
		//get the hoist status and write it into the buffer
		switch (msg_getstatus(msg)) {
			case UP:
				sprintf(buffer, "Hoist going up");
				break;
			case DOWN:
				sprintf(buffer, "Hoist going down");
				break;
			case STOP:
				sprintf(buffer, "Hoist stopped");
				break;
			case TOP:
				sprintf(buffer, "Maximal height reached");
				break;
			case BOTTOM:
				sprintf(buffer, "Minimal height reached");
				break;
			case EXIT:
				sprintf(buffer, "Exiting");
				break;
		}
		//print the hoist height and status
		printf("height: %3d cm\tstatus: %s\n", msg_getheight(msg), buffer); fflush(stdout);
	}


	fprintf(log, "%s: exiting\n", NAME); fflush(log);
	//free the memory occupied by the message
	msg_free(msg);
	//close socket and log file descriptors before exiting
	close(fd_log);
	close(sockfd);

  exit (0);
}
