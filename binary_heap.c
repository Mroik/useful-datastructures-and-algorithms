void sift_down(int* data, int index, int size)
{
	int i = index;
	int l, r;
	int greater = i;

	while (i < size) {
		l = i * 2 + 1;
		r = i * 2 + 1;
		if (l >= size)
			break;

		if (data[i] < data[l])
			greater = l;

		if (r < size && data[greater] < data[r])
			greater = r;

		if (greater == i)
			break;

		int temp = data[greater];
		data[greater] = data[i];
		data[i] = temp;
		i = greater;
	}
}

int* make_heap(int* from, int size)
{
	for (int x = size - 1; x >= 0; x--)
		sift_down(from, x, size);
}

int pop(int* data, int size)
{
	int ris = data[0];
	data[0] = data[size - 1];
	size--;
	sift_down(data, 0, size);
	return ris;
}
