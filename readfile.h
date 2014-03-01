#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define BF_COUNT 8
#define BF_SIZE 512

struct bloom {
	uint64_t bit_array[BF_SIZE / 8];
};

struct leaf_desc {
	int *leaf;
	int count;
	int first_num;
	struct bloom bloom;;
};

struct list_desc {
	void *ptr; // Point to a leaf or root
	int leaf;
	int count;
	int list_id;
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
