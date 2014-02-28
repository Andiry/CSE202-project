#include "readfile.h"

void list_intersection(struct list_desc *keywords, int keyword_count)
{
	int i;

	for (i = 0; i < keyword_count; i++)
		printf("keyword %d: count %d\n",
			keywords[i].list_id, keywords[i].count);

}
