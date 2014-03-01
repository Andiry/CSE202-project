#include "readfile.h"

int search_in_list(struct list_desc *keywords, int target, int id, int *disk_io)
{
	int curr_num;
	int curr_index;
	struct leaf_desc *root;
	int *curr_leaf;
	int count;
	int i;
	int leaf_count;
	int num_count;

	count = keywords[id].count;

	if (keywords[id].leaf) {
		curr_leaf = (int *)keywords[id].ptr;
		leaf_count = 1;
	} else {
		root = (struct leaf_desc *)keywords[id].ptr;
		leaf_count = count / 1024;
		leaf_count += count % 1024 ? 1 : 0;
	}

	for (i = 0; i < leaf_count; i++) {
		if (keywords[id].leaf) {
			num_count = count;
		} else {
			curr_leaf = root[i].leaf;
			num_count = root[i].count;
		}

		if (binary_search(curr_leaf, target, num_count)) {
			if (!keywords[id].leaf)
				*disk_io = *disk_io + i + 1;
			return 1;
		}
	}

	if (!keywords[id].leaf)
		*disk_io += leaf_count;
	return 0;
}

