#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void set_list_name(char *list, int d)
{
	char c[20];

	if (d >= 100000)
		assert(0);

	sprintf(c, "%d", d);
	strcpy(list + 8, c);
}

static void set_query_name(char *queries, int d)
{
	char c[20];

	if (d >= 1000000)
		assert(0);

	sprintf(c, "%d", d);
	strcpy(queries + 10, c);
}

void handle_query(char *queries, int query)
{
	FILE *fp;
	int d;
	char *list;

	list = malloc(32);
	if (!list)
		return;

	strcpy(list, "./lists/");

	set_query_name(queries, query);

	fp = fopen(queries, "r");
	if (!fp) {
		printf("%s does not exist!\n", queries);
		goto fail;
	}

	while(fscanf(fp, "%d", &d) != EOF)
	{
		printf("list %d\n", d);
		set_list_name(list, d); 
		printf("%s\n", list);
	}

	printf("\n");

fail:
	free(list);
	fclose(fp);
}

int main(void)
{
	char *queries;

	queries = malloc(32);
	if (!queries)
		return 0;

	strcpy(queries, "./queries/");

	handle_query(queries, 0);

	free(queries);
	return 0;
}
