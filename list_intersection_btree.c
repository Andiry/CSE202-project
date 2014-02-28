#include "readfile.h"

void list_intersection(struct list_desc *keywords, int keyword_count)
{
	int i;
	int min_count;
	int min_id, min_list_id;
	int curr_index;
	int curr_leaf_index;
	struct leaf_desc *root;
	int *curr_leaf;

	if (keyword_count < 2) {
		printf("Just %d keywords. Cannot find intersection list\n",
			keyword_count);
		return;
	}

	min_count = keywords[0].count;
	min_list_id = keywords[0].list_id;
	min_id = 0;

	for (i = 0; i < keyword_count; i++) {
		printf("keyword %d: count %d\n",
			keywords[i].list_id, keywords[i].count);
		if (min_count > keywords[i].count) {
			min_count = keywords[i].count;
			min_list_id = keywords[i].list_id;
			min_id = i;
		}
	}

	printf("Min keyword %d: count %d, in list %d\n",
		min_list_id, min_count, min_id);

	if (keywords[min_id].leaf) {
		curr_leaf = (int *)keywords[min_id].ptr;
	} else {
		root = (struct leaf_desc *)keywords[min_id].ptr;
	}

	for (i = 0; i < min_count; i++) {
		if (keywords[min_id].leaf) {
			curr_index = curr_leaf[i];
		} else {
			curr_leaf_index = i / 1024;
			curr_leaf = root[curr_leaf_index].leaf;
			curr_index = curr_leaf[i % 1024];
		}
//		printf("%d\t", curr_index);
	}

}
