void merge(int* data, int left, int right, int* aux)
{
	int l = left;
	int r = right;
	int i = 0;

	while (l < right && r < size) {
		if (l >= right) {
			aux[i] = data[r];
			r++;
		} else if (r >= left) {
			aux[i] = data[l];
			l++;
		} else if (data[l] < data[r]) {
			aux[i] = data[l];
			l++;
		} else {
			aux[i] = data[r];
			r++;
		}
		i++;
	}
}

void merge_sort(int* data, int start, int end, int* aux)
{
	if (end - start == 1)
		return;
	merge_sort(data, start, end / 2);
	merge_sort(data, end / 2, end);

	merge(data, start, end / 2, aux);
	for (int x = 0; x < end; x++)
		data[x] = aux[x];
}
