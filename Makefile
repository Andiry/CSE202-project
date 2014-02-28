CC = gcc
CFLAGS = -O3
CLIB = -lrt -lpthread

SRCS = $(wildcard *.c)
BUILD = linear binary btree

common_objects = readfile.o update_list.o

linear_objects = $(common_objects) linear_search.o 
binary_objects = $(common_objects) binary_search.o 
btree_objects = $(common_objects) btree_search.o 

all: $(BUILD)

linear : $(linear_objects) 
	$(CC) $(CFLAGS) $(linear_objects) -o $@ $(CLIB)

binary : $(binary_objects) 
	$(CC) $(CFLAGS) $(binary_objects) -o $@ $(CLIB)

btree : $(btree_objects) 
	$(CC) $(CFLAGS) $(btree_objects) -o $@ $(CLIB)

clean:
	rm -rf *.o $(BUILD)

