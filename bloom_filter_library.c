#include "readfile.h"

void set_bloom_filter(struct leaf_desc *root, int leaf_id, int count)
{
	int *leaf = root[leaf_id].leaf;
	struct bloom *bloom = &(root[leaf_id].bloom);
	unsigned int seed = 0;
	unsigned int hash = 0;
	int i, j;
	int num;
	int pos;
	int array_id, array_index;

	for (i = 0; i < count; i++) {
		num = leaf[i];
//		printf("%d\n", num);

		for (j = 0; j < BF_COUNT; j++) {
			hash = Murmur3_32(num, seed);
			seed = hash;
			pos = hash % 512;

			array_id = pos / 64;
			array_index = pos % 64;

			bloom->bit_array[array_id] |= 1 << array_index;
		}
	}
}

int check_bloom_filter(struct leaf_desc *root, int leaf_id, int target)
{
	int *leaf = root[leaf_id].leaf;
	struct bloom *bloom = &(root[leaf_id].bloom);
	unsigned int seed = 0;
	unsigned int hash = 0;
	int i;
	int pos;
	int array_id, array_index;

//	printf("%s\n", __func__);
	for (i = 0; i < BF_COUNT; i++) {
		hash = Murmur3_32(target, seed);
		seed = hash;
		pos = hash % 512;

		array_id = pos / 64;
		array_index = pos % 64;

		if ((bloom->bit_array[array_id] & (1ULL << array_index)) == 0)
			return 0;
	}

	return 1;
}
