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

