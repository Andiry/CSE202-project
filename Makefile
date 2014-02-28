CC = gcc
CFLAGS = -O3
CLIB = -lrt -lpthread

SRCS = $(wildcard *.c)
BUILD = getlist_btree

btree_objects = readfile.o list_intersection_btree.o 

all: $(BUILD)

getlist_btree : $(btree_objects) 
	$(CC) $(CFLAGS) $(btree_objects) -o $@ $(CLIB)

clean:
	rm -rf *.o $(BUILD)

