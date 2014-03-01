#include "readfile.h"

int binary_search_leaf_id(struct leaf_desc *root, int leaf_count, int target)
{
	int start = 0;
	int end = leaf_count - 1;
	int middle;

	if (root[0].first_num > target)
		return -1;

	if (root[end].first_num <= target)
		return end;

	while (start <= end) {
		middle = (start + end) / 2;
		if (root[middle].first_num > target)
			end = middle - 1;
		else if (root[middle + 1].first_num <= target)
			start = middle + 1;
		else
			return middle;
	}

	return -1;

}

int search_in_list(struct list_desc *keywords, int target, int id, int *disk_io)
{
	struct leaf_desc *root;
	int *curr_leaf;
	int count;
	int leaf_count;
	int leaf_id;
	int num_count;

	count = keywords[id].count;

	if (keywords[id].leaf) {
		curr_leaf = (int *)keywords[id].ptr;
		leaf_count = 1;
		if (binary_search(curr_leaf, target, count))
			return 1;
	} else {
		root = (struct leaf_desc *)keywords[id].ptr;
		leaf_count = count / 1024;
		leaf_count += count % 1024 ? 1 : 0;

		leaf_id = binary_search_leaf_id(root, leaf_count, target);

		if (leaf_id >= 0 && check_bloom_filter(root, leaf_id, target)) {
			curr_leaf = root[leaf_id].leaf;
			num_count = root[leaf_id].count;
			(*disk_io)++;
			if (binary_search(curr_leaf, target, num_count))
				return 1;
		}
	}

	return 0;
}

