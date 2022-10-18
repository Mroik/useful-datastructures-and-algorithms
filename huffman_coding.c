#include <stdlib.h>

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
	return father;
}

// Use a heapsort if you want it efficent
void sort(node** nodes, int size)
{
	node* temp;
	for(int x = 0; x < size - 1; x++)
	{
		for(int y = x + 1; y < size; y++)
		{
			if(nodes[y]->freq < nodes[x]->freq)
			{
				temp = nodes[y];
				nodes[y] = nodes[x];
				nodes[x] = temp;
			}
		}
	}
}

void count(char* string, int* counters)
{
	for(int x = 0; x < 256; x++)
		counters[x] = 0;
	for(int x = 0; string[x] != 0; x++)
		counters[string[x]]++;
}

// Assuming only ASCII
int make_tree(char* string, node*** nodes, node** root)
{
	int counters[256];
	int tot_nodes = 0;
	int tt;
	int i_nodes = 0;

	count(string, counters);
	for(int x = 0; x < 256; x++)
	{
		if(counters[x] != 0)
			tot_nodes++;
	}

	*nodes = malloc(sizeof(node*) * tot_nodes);

	// Make array of nodes
	for(int x = 0; x < 256; x++)
	{
		if(counters[x] != 0)
		{
			(*nodes)[i_nodes] = make_node(x, counters[x]);
			i_nodes++;
		}
	}

	node** temp[tot_nodes];
	for(int x = 0; x < tot_nodes; x++)
		temp[x] = (*nodes)[x];

	// Start generating tree
	tt = tot_nodes;
	sort(temp, tt);
	while(tt < 2)
	{
		temp[1] = make_father(temp[0], temp[1]);
		temp++;
	}
	*root = temp[0];
	return tot_nodes;
}
