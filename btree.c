#include "readfile.h"

int search_in_list(struct list_desc *keywords, int target, int id,
			int *disk_io, enum algorithm *type, int *bf_error)
{
	struct leaf_desc *root;
	int *curr_leaf;
	int count;
	int leaf_count;
	int leaf_id;
	int num_count;

	count = keywords[id].count;
	*type = BTREE;

	if (keywords[id].leaf) {
		curr_leaf = (int *)keywords[id].ptr;
		leaf_count = 1;
		if (binary_search(curr_leaf, target, count))
			return 1;
	} else {
		root = (struct leaf_desc *)keywords[id].ptr;
		leaf_count = count / INDEX_PER_LEAF;
		leaf_count += count % INDEX_PER_LEAF ? 1 : 0;

		leaf_id = binary_search_leaf_id(root, leaf_count, target);

		if (leaf_id >= 0) {
			(*disk_io)++;
			curr_leaf = root[leaf_id].leaf;
			num_count = root[leaf_id].count;
			if (binary_search(curr_leaf, target, num_count))
				return 1;
		}
	}

	return 0;
}

