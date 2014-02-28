CC = gcc
CFLAGS = -O3
CLIB = -lrt -lpthread

SRCS = $(wildcard *.c)
BUILD = linear binary

common_objects = readfile.o update_list.o

linear_objects = $(common_objects) linear_search.o 
binary_objects = $(common_objects) binary_search.o 

all: $(BUILD)

linear : $(linear_objects) 
	$(CC) $(CFLAGS) $(linear_objects) -o $@ $(CLIB)

binary : $(binary_objects) 
	$(CC) $(CFLAGS) $(binary_objects) -o $@ $(CLIB)

clean:
	rm -rf *.o $(BUILD)

