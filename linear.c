#include "readfile.h"

int search_in_list(struct list_desc *keywords, int target, int id,
			int *disk_io, enum algorithm *type)
{
	int curr_num;
	int curr_index;
	int curr_leaf_index = 0;
	struct leaf_desc *root;
	int *curr_leaf;
	int count;
	int i;

	count = keywords[id].count;
	*type = LINEAR;

	if (keywords[id].leaf) {
		curr_leaf = (int *)keywords[id].ptr;
	} else {
		root = (struct leaf_desc *)keywords[id].ptr;
	}

	for (i = 0; i < count; i++) {
		if (keywords[id].leaf) {
			curr_index = i;
		} else {
			curr_leaf_index = i / 1024;
			curr_leaf = root[curr_leaf_index].leaf;
			curr_index = i % 1024;
		}

		curr_num = curr_leaf[curr_index];

		if (curr_num == target) {
			if (!keywords[id].leaf)	
				*disk_io = *disk_io + curr_leaf_index + 1;
			return 1;
		}
	}

	if (!keywords[id].leaf)	
		*disk_io = *disk_io + curr_leaf_index + 1;
	return 0;
}

