struct leaf_desc {
	int *leaf;
	int count;
	int first_num;
};

struct list_desc {
	void *ptr; // Point to a leaf or root
	int leaf;
	int count;
	int list_id;
};
