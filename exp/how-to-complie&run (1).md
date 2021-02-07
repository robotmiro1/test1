---> how to Compile and Run
***************************

COMPILE: To ease the compiling operation I used a makefile. The purpose of a makefile is to be easily build an executable that might take many commands to create.

Three slightly different commands can be issued to compile different subsets
of the entirety of the scripts. This is in order to allow for both distribution of the sole
executables (in which case the first command is the faster approach) or of the source
code themselves (in which case the two parts, server and client, might need to be compiled on two
different machines).

1) The "make" determine automatically which pieces of a program need to be recompiled and isue the command to recompile them.
2) The "make crane_server" is used to compile only the scripts referring to the server side, that is the server itself and the crane "simulator".
3) We use also "make hoist_interface" to compile only the scripts referring to the client side, that is the "input" and the "output" user interface.

RUN: the server can be runned by providing the port it should listen to for the communication:

 ./server 'number of Port'

While the client will need the public address of the machine the server is running on together
with the port to direct data to:

 ./client 'IP address' 'number of Port'
