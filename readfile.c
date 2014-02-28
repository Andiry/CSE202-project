#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "readfile.h"

static void set_list_filename(char *list_file, int d)
{
	char c[20];

	if (d >= 100000)
		assert(0);

	sprintf(c, "%d", d);
	strcpy(list_file + 8, c);
}

static void set_query_filename(char *query_file, int d)
{
	char c[20];

	if (d >= 1000000)
		assert(0);

	sprintf(c, "%d", d);
	strcpy(query_file + 10, c);
}

void read_list_file(char *list_file, int id)
{
	FILE *fp;
	int d;
	int i;
	int count = 0;
	int *leaf = NULL;
	struct leaf_desc *root = NULL;
	int leaf_id = 0; // Current ith leaf
	int index_id;	 // Current number id in leaf

	fp = fopen(list_file, "r");
	if (!fp) {
		printf("%s does not exist!\n", list_file);
		return;
	}

	/* Leaf is PAGE_SIZE. */
	leaf = malloc(sizeof(int) * 1024);
	if (!leaf) {
		printf("leaf allocation failed!\n");
		goto fail;
	}
 
	while(fscanf(fp, "%d", &d) != EOF)
	{
		if (count == 0) {
			/* The first number is list id. Ignore it */
			count++;
			continue;
		}

		index_id = count - leaf_id * 1024 - 1; 
		if (index_id < 1024) {
			leaf[index_id] = d;
		} else {
			/* We need a new leaf */
			if (leaf_id == 0) {
				/* Allocate root */
				root = malloc(sizeof(struct leaf_desc) * 1024);
				if (!root)
					goto root_fail;
				root[0].leaf = leaf;
				root[0].count = 1024;
				root[0].first_num = leaf[0];
			}

			leaf_id++;
			leaf = malloc(sizeof(int) * 1024);
			if (!leaf)
				goto new_leaf_fail;

			leaf[0] = d;
			root[leaf_id].leaf = leaf;
			root[leaf_id].first_num = leaf[0];
		}

		count++;
	}

	if (count <= 1)
		goto root_fail;

	printf("list %d: total %d numbers, %d leafs\n",
		id, count - 1, leaf_id + 1);

	if (root) {
		root[leaf_id].count = index_id + 1;
		printf("last leaf contains %d numbers\n", root[leaf_id].count);
		for (i = 0; i <= leaf_id; i++)
			printf("%d\t", root[i].first_num);
		printf("\n");
	}

	return;

new_leaf_fail:
	for (i = 0; i < leaf_id; i++)
		free(root[i].leaf);
	free(root);
	leaf = NULL;
root_fail:
	free(leaf);
fail:
	fclose(fp);

}

void handle_query(char *query_file, int query)
{
	FILE *fp;
	int d;
	char *list_file;

	list_file = malloc(32);
	if (!list_file)
		return;

	strcpy(list_file, "./lists/");

	set_query_filename(query_file, query);

	fp = fopen(query_file, "r");
	if (!fp) {
		printf("%s does not exist!\n", query_file);
		goto fail;
	}

	while(fscanf(fp, "%d", &d) != EOF)
	{
		printf("list_file %d\n", d);
		set_list_filename(list_file, d); 
		printf("%s\n", list_file);
		read_list_file(list_file, d);
	}

	printf("\n");

fail:
	free(list_file);
	fclose(fp);
}

int main(void)
{
	char *query_file;

	query_file = malloc(32);
	if (!query_file)
		return 0;

	strcpy(query_file, "./queries/");

	handle_query(query_file, 0);

	free(query_file);
	return 0;
}
