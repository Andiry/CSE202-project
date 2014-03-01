CC = gcc
CFLAGS = -O3
CLIB = -lrt -lpthread

SRCS = $(wildcard *.c)
BUILD = linear binary btree bloom_filter

common_objects = readfile.o update_list.o binary_search.o \
		 bloom_filter_library.o murmurHash.o

linear_objects = $(common_objects) linear.o 
binary_objects = $(common_objects) binary.o 
btree_objects = $(common_objects) btree.o 
bloom_filter_objects = $(common_objects) bloom_filter.o 

all: $(BUILD)

linear : $(linear_objects) 
	$(CC) $(CFLAGS) $(linear_objects) -o $@ $(CLIB)

binary : $(binary_objects) 
	$(CC) $(CFLAGS) $(binary_objects) -o $@ $(CLIB)

btree : $(btree_objects) 
	$(CC) $(CFLAGS) $(btree_objects) -o $@ $(CLIB)

bloom_filter : $(bloom_filter_objects) 
	$(CC) $(CFLAGS) $(bloom_filter_objects) -o $@ $(CLIB)

clean:
	rm -rf *.o $(BUILD)

