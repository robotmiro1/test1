all: hoist server client reader clean

hoist_server: hoist server clean

hoist_interface: client reader clean

hoist: hoist.o hoistlib.o
	gcc $^ -g -o $@
server: server.o hoistlib.o
	gcc $^ -g -o $@
client: client.o hoistlib.o
	gcc $^ -g -o $@
reader: reader.o hoistlib.o
	gcc $^ -g -o $@

hoist.o: hoist.c
	gcc -c $<
server.o: server.c
	gcc -c $<
client.o: client.c
	gcc -c $<
reader.o: reader.c
	gcc -c $<
	
hoistlib.o: hoistlib.c hoistlib.h
	gcc -c $<

.PHONY: clean

clean:
	rm -f hoist.o
	rm -f server.o
	rm -f client.o
	rm -f reader.o
	rm -f hoistlib.o