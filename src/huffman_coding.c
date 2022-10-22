#include <stdlib.h>
#include <stdio.h>

typedef struct node_r {
	char value;
	int freq;
	struct node_r* father;
	struct node_r* left;
	struct node_r* right;
} node;

node* make_node(char value, int freq)
{
	node* new_node = malloc(sizeof(node));
	new_node->value = value;
	new_node->freq = freq;
	new_node->father = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

node* make_father(node* left, node* right)
{
	node* father = make_node(0, left->freq + right->freq);
	father->left = left;
	father->right = right;
	left->father = father;
	right->father = father;
	return father;
}

// Use a heapsort if you want it efficent
void sort(node** nodes, int size)
{
	node* temp;
	for (int x = 0; x < size - 1; x++) {
		for (int y = x + 1; y < size; y++) {
			if (nodes[y]->freq < nodes[x]->freq) {
				temp = nodes[y];
				nodes[y] = nodes[x];
				nodes[x] = temp;
			}
		}
	}
}

void count(char* string, int (*counters)[])
{
	for (int x = 0; x < 256; x++)
		(*counters)[x] = 0;
	for (int x = 0; string[x] != 0; x++)
		(*counters)[string[x]]++;
}

void bubble_sort(node** nodes, int size)
{
	for (int x = 0; x < size - 1; x++) {
		if (nodes[x]->freq > nodes[x + 1]->freq) {
			node* temp = nodes[x];
			nodes[x] = nodes[x + 1];
			nodes[x + 1] = temp;
		}
	}
}

// Assuming only ASCII
int make_tree(char* string, node*** nodes, node** root)
{
	int counters[256];
	int tot_nodes = 0;
	int tt;
	int i_nodes = 0;

	count(string, &counters);
	for (int x = 0; x < 256; x++) {
		if (counters[x] != 0)
			tot_nodes++;
	}

	*nodes = malloc(sizeof(node*) * tot_nodes);

	// Make array of nodes
	for (int x = 0; x < 256; x++) {
		if (counters[x] != 0) {
			(*nodes)[i_nodes] = make_node(x, counters[x]);
			i_nodes++;
		}
	}

	node* n_array[tot_nodes];
	node** temp = n_array;
	for (int x = 0; x < tot_nodes; x++)
		temp[x] = (*nodes)[x];

	// Start generating tree
	tt = tot_nodes;
	sort(temp, tt);
	while (tt > 1) {
		temp[1] = make_father(temp[0], temp[1]);
		temp++;
		tt--;
		bubble_sort(temp, tt);
	}
	*root = temp[0];
	return tot_nodes;
}

void encode(node* node, char* buffer, int offset)
{
	if (node->father == NULL) {
		buffer[offset] = 0;
		for (int x = 0; x < offset / 2; x++) {
			char temp = buffer[x];
			buffer[x] = buffer[offset - 1 - x];
			buffer[offset - 1 - x] = temp;
		}
		return;
	}

	buffer[offset] = node->father->left == node ? '0' : '1';
	encode(node->father, buffer, offset + 1);
}

char decode(node* root, char* buffer, int offset)
{
	if (buffer[offset] == 0)
		return root->value;
	if (buffer[offset] == '0')
		decode(root->left, buffer, offset + 1);
	else
		decode(root->right, buffer, offset + 1);
}

// The implementation ends here

void debug(node* root, int layer)
{
	if (root == NULL)
		return;

	if (root->left == NULL || root->right == NULL)
		printf("char: %c freq: %d layer: %d\n", root->value, root->freq, layer);

	if (root->left != NULL)
		debug(root->left, layer + 1);
	if (root->right != NULL)
		debug(root->right, layer + 1);
}

int load_from_file(char** buffer) {
	FILE* fp = fopen("../commedia.txt", "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	*buffer = malloc(sizeof(char) * size);
	rewind(fp);
	for(int x = 0; x < size; x++)
		(*buffer)[x] = fgetc(fp);
	fclose(fp);
	return size;
}

// Newlines mess up the output on the summary
void strip_newline(char* buffer) {
	for (int x = 0; buffer[x] != 0; x++) {
		if (buffer[x] == 0xA || buffer[x] == 0xD)
			buffer[x] = ' ';
	}
}

// Here an example of the usage
int main()
{
	char* text;
	int size;
	node** nodes;
	node* root;

	load_from_file(&text);
	strip_newline(text);
	size = make_tree(text, &nodes, &root);
	debug(root, 0);
	for (int x = 0; x < size; x++)
		printf("%c %d\n", nodes[x]->value, nodes[x]->freq);

	// Should cycle through text and search the corrisponding node
	// for every character in text and then encode/decode. Too lazy
	// to do that here.
	char buf[20];
	for (int x = 0; x < size; x++) {
		encode(nodes[x], buf, 0);
		printf("%c %s %c\n", nodes[x]->value, buf, decode(root, buf, 0));
	}
	// Remember to free the allocated memory (to lazy to do that here)
}
