#include "readfile.h"

int search_in_list(struct list_desc *keywords, int target, int id,
			int *disk_io, enum algorithm *type, int *bf_error)
{
	struct leaf_desc *root = NULL;
	int *curr_leaf = NULL;
	int count;
	int i;
	int leaf_count;
	int num_count;

	count = keywords[id].count;
	*type = BINARY;

	if (keywords[id].leaf) {
		curr_leaf = (int *)keywords[id].ptr;
		leaf_count = 1;
	} else {
		root = (struct leaf_desc *)keywords[id].ptr;
		leaf_count = count / INDEX_PER_LEAF;
		leaf_count += count % INDEX_PER_LEAF ? 1 : 0;
	}

	for (i = 0; i < leaf_count; i++) {
		if (keywords[id].leaf) {
			num_count = count;
		} else {
			curr_leaf = root[i].leaf;
			num_count = root[i].count;
			if (root[i].first_num > target)
				break;
		}

		if (binary_search(curr_leaf, target, num_count)) {
			if (!keywords[id].leaf)
				*disk_io = *disk_io + i + 1;
			return 1;
		}
	}

	if (!keywords[id].leaf)
		*disk_io += i;
	return 0;
}

