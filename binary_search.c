#include "readfile.h"

int binary_search(int *leaf, int target, int count)
{
	int start = 0;
	int end = count - 1;
	int middle;

	while (start <= end) {
		middle = (start + end) / 2;
		if (leaf[middle] == target)
			return 1;
		else if (leaf[middle] > target)
			end = middle - 1;
		else
			start = middle + 1;
	}

	return 0;

}

int search_in_list(struct list_desc *keywords, int target, int id)
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

		if (binary_search(curr_leaf, target, num_count))
			return 1;
	}

	return 0;
}

