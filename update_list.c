#include "readfile.h"

static void update_min_list(struct list_desc *keywords, int min_id, int curr_id,
				int *disk_io, enum algorithm *type)
{
	int i;
	int curr_num;
	int curr_index;
	int curr_leaf_index;
	struct leaf_desc *root = NULL;
	int *curr_leaf = NULL;
	int min_count;
	int ret;

	min_count = keywords[min_id].count;

	if (keywords[min_id].leaf) {
		curr_leaf = (int *)keywords[min_id].ptr;
	} else {
		root = (struct leaf_desc *)keywords[min_id].ptr;
	}

	for (i = 0; i < min_count; i++) {
		if (keywords[min_id].leaf) {
			curr_index = i;
		} else {
			curr_leaf_index = i / 1024;
			curr_leaf = root[curr_leaf_index].leaf;
			curr_index = i % 1024;
		}
//		printf("%d\t", curr_index);
		curr_num = curr_leaf[curr_index];

		if (curr_num == 0) continue;

		ret = search_in_list(keywords, curr_num, curr_id,
					disk_io, type);

		if (!ret)
			curr_leaf[curr_index] = 0;
	}

}

static void print_result(struct list_desc *keywords, int id)
{
	int curr_num;
	int curr_index;
	int curr_leaf_index;
	struct leaf_desc *root = NULL;
	int *curr_leaf = NULL;
	int count;
	int i;
	int total = 0;

	count = keywords[id].count;

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

		if (curr_num) {
			total++;
//			printf("%d\t", curr_num);
		}
	}

	printf("Total: %d\n", total);
	return;
}

void list_intersection(struct list_desc *keywords, int keyword_count)
{
	int i;
	int min_count;
	int min_id, min_list_id;
	struct timespec start, end;
	long long time;
	int disk_io;
	enum algorithm type;

	if (keyword_count < 2) {
		printf("Just %d keywords. Cannot find intersection list\n",
			keyword_count);
		return;
	}

	min_count = keywords[0].count;
	min_list_id = keywords[0].list_id;
	min_id = 0;

	for (i = 0; i < keyword_count; i++) {
//		printf("keyword %d: count %d\n",
//			keywords[i].list_id, keywords[i].count);
		if (min_count > keywords[i].count) {
			min_count = keywords[i].count;
			min_list_id = keywords[i].list_id;
			min_id = i;
		}
	}

//	printf("Min keyword %d: count %d, in list %d\n",
//		min_list_id, min_count, min_id);

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (i = 0; i < keyword_count; i++) {
		if (i == min_id)
			continue;

		update_min_list(keywords, min_id, i, &disk_io, &type);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
	print_result(keywords, min_id);
	printf("Algorithm %d: Use %lld nanoseconds, disk IO %d\n", type,
			time, disk_io);

}
