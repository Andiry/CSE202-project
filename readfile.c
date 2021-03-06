#include "readfile.h"

int BF_COUNT;
int BF_SIZE;

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

static int read_list_file(struct list_desc *desc, char *list_file,
				int id, int bf)
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
		return -1;
	}

	/* Leaf is PAGE_SIZE. */
	leaf = malloc(sizeof(int) * INDEX_PER_LEAF);
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

		index_id = count - leaf_id * INDEX_PER_LEAF - 1; 
		if (index_id < INDEX_PER_LEAF) {
			leaf[index_id] = d;
		} else {
			/* We need a new leaf */
			if (leaf_id == 0) {
				/* Allocate root */
				root = malloc(sizeof(struct leaf_desc)
						* LEAF_PER_ROOT);
				if (!root)
					goto root_fail;
				memset(root, 0, sizeof(root));
				root[0].leaf = leaf;
				root[0].first_num = leaf[0];
			}

			root[leaf_id].count = INDEX_PER_LEAF;
			if (bf)
				set_bloom_filter(root, leaf_id, INDEX_PER_LEAF);

			leaf_id++;
			leaf = malloc(sizeof(int) * INDEX_PER_LEAF);
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

	if (root) {
		root[leaf_id].count = index_id + 1;
		if (bf)
			set_bloom_filter(root, leaf_id, index_id + 1);
	}

	desc->count = count - 1;
	desc->leaf = root ? 0 : 1;
	desc->list_id = id;
	desc->ptr = root ? (void *)root : (void *)leaf;

	fclose(fp);
	return 0;

new_leaf_fail:
	for (i = 0; i < leaf_id; i++)
		free(root[i].leaf);
	free(root);
	leaf = NULL;
root_fail:
	free(leaf);
fail:
	fclose(fp);
	return -1;

}

static void free_root(void* root, int count)
{
	int leaf_count;
	int i;
	struct leaf_desc* leafs = (struct leaf_desc *)root;

	leaf_count = count / INDEX_PER_LEAF;
	leaf_count = count % INDEX_PER_LEAF ? leaf_count + 1 : leaf_count;

	for (i = 0; i < leaf_count; i++) {
		free(leafs[i].leaf);
	}

	free(leafs);
}

static void cleanup_keywords(struct list_desc *keywords, int keyword_count)
{
	int i;
	struct list_desc *desc;

	for (i = 0; i < keyword_count; i++) {
		desc = keywords + i;
		if (desc->ptr) {
			if (desc->leaf)
				free(desc->ptr);
			else
				free_root(desc->ptr, desc->count);
		}
	}

	free(keywords);
}

static void handle_query(char *query_file, int query, int bf, FILE *output)
{
	FILE *fp;
	int d;
	int i = 0;
	char *list_file;
	struct list_desc *keywords;
	int keyword_count = 0;

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
		keyword_count++;
	fclose(fp);

	keywords = malloc(sizeof(struct list_desc) * keyword_count);
	if (!keywords)
		goto fail;
	memset(keywords, 0, sizeof(keywords));

	fp = fopen(query_file, "r");
	while(fscanf(fp, "%d", &d) != EOF)
	{
//		printf("list_file %d\n", d);
		set_list_filename(list_file, d); 
//		printf("%s\n", list_file);
		if (read_list_file(keywords + i, list_file, d, bf)) {
			printf("read_list_file failed! Cleanup.\n");
			goto list_fail;
		}
		i++;
	}

	list_intersection(keywords, keyword_count, query, output);

list_fail:
	cleanup_keywords(keywords, keyword_count);

	fclose(fp);
fail:
	free(list_file);
}

int main(int argc, char **argv)
{
	int query;
	int bf_enabled;
	char *query_file;
	char filename[60];
	FILE *output;

	if (argc < 6) {
		printf("Usage: ./exec $query $use_bloom_filter $output_file $BF_COUNT $BF_SIZE\n");
		return 0;
	}

	query = atoi(argv[1]);
	bf_enabled = atoi(argv[2]);
	strcpy(filename, argv[3]);
	BF_COUNT = atoi(argv[4]);
	BF_SIZE = atoi(argv[5]);

	output = fopen(filename, "a");
	if (!output)
		return 0;

	query_file = malloc(32);
	if (!query_file)
		return 0;

	strcpy(query_file, "./queries/");

	handle_query(query_file, query, bf_enabled, output);

	free(query_file);
	fclose(output);

	return 0;
}
