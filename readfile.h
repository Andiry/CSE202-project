#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define BF_COUNT 8	// Hash cycles
#define BF_SIZE 512	// Bloom filter table size (byte)

struct bloom {
	uint64_t bit_array[BF_SIZE / 8];
};

struct leaf_desc {
	int *leaf;		// Pointer to the leaf (4KB)
	int count;		// # of numbers in this leaf
	int first_num;		// The first number in the leaf
	struct bloom bloom;	// Bloom filter
};

struct list_desc {
	void *ptr; 	// Either point to a leaf or root (leaf_desc)
	int leaf;	// Indicate this is a leaf or root
	int count;	// Total # of numbers
	int list_id;	// The keyword id
};

void list_intersection(struct list_desc *keywords, int keyword_count);
int search_in_list(struct list_desc *keywords, int target, int id, int *disk_io);

/* binary search */
int binary_search(int *leaf, int target, int count);

/* bloom filter functions */
void set_bloom_filter(struct leaf_desc *root, int leaf_id, int count);
int check_bloom_filter(struct leaf_desc *root, int leaf_id, int target);

/* Hash function */
unsigned int Murmur3_32(int key, int seed);
