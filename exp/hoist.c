#include "hoistlib.h"
#include <netinet/in.h>
#include <sys/socket.h>

//Comment No1
//to avoid problems with multiple processes trying to add to it ,the log
//file is opened from a file descriptor passed from the master process

int main(int argc, char *argv[])
{
	
        const char *NAME = "HOIST";                            //process name for the log file
	int fd_in, fd_out;
	char in=0, ret;
	int height=0;

	FILE *log;
	int fd_log;

//check number of arguments provided
	if (argc<4){
		fprintf(stderr,"ERROR too few arguments passed\n");
		exit(1);
	}

//open the log file
	fd_log = atoi(argv[1]);
	if((log = fdopen(fd_log, "w"))==(FILE*)NULL){
		perror("HOIST: Log file open from filedes");
	}
//get pipe file descriptors
	fd_in = atoi(argv[2]);
	fd_out = atoi(argv[3]);
	fprintf(log, "%s: starting\n", NAME); fflush(log);

//until the EXIT command is received from the server
	while(in!= EXIT){
		in = 0;	
// for the command above: to avoid it retaining previous values and potentially keep moving in case of red errors
//read the command from the server
		if((ret = read(fd_in, &in, 1))<0) error("ERROR reading from Server - Hoist pipe", ret);

	//move the hoist (or don't move it)
		switch (in){
			case '+':	 // go UP
				height_tryup(&height);
				break;
			case '-': 	// go DOWN
				height_trydown(&height);
				break;
	// default: // will simply do nothing
		}
	//send the current height to the server
		if((ret = write(fd_out, &height, sizeof(int)))<0) error("ERROR writing to Hoist - Server pipe", ret);
	}
	fprintf(log, "%s: exiting\n", NAME); fflush(log);
	//close pipe and log file descriptors
	close(fd_log);
	close(fd_in);
	close(fd_out);

	return 0;
}
