unsigned int Murmur3_32(int key, int seed)
{
	unsigned int c1 = 0xcc9e2d51;
	unsigned int c2 = 0x1b873593;
	int r1 = 15;
	int r2 = 13;
	int m = 5;
	unsigned int n = 0xe6546b64;
	unsigned int hash = (unsigned int)seed;
	unsigned int k = (unsigned int)key;
 
	k = k * c1;
	k = (k << r1) | (k >> (32 - r1));
	k = k * c2;

	hash = hash ^ k;
	hash = (hash << r2) | (hash >> (32 - r2));
	hash = hash * m + n;

	hash = hash ^ 32;

	hash = hash ^ (hash >> 16);
	hash = hash * 0x85ebca6b;
	hash = hash ^ (hash >> 13);
	hash = hash * 0xc2b2ae35;
	hash = hash ^ (hash >> 16);

	return hash;
}
