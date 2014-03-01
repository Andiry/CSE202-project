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

