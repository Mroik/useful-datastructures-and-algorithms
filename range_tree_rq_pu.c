// Range query point update
#include <stdlib.h>

typedef struct node_r {
	int value;
	int start;
	int end;
	struct node_r* father;
	struct node_r* left;
	struct node_r* right;
} node;

node* make_node(int value, int start, int end)
{
	node* new_node = malloc(sizeof(node));
	new_node->value = value;
	new_node->start = start;
	new_node->end = end;
	new_node->father = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

// This tree in particular is used to query the sum of
// the items of the specified range. It is not the only
// way to use it. The implementation could be changed so
// that each nodes stores the max value of it's range.
node* build_father(node* left, node* right)
{
	int v_left, v_right, start, end;
	v_left = left == NULL ? 0 : left->value;
	v_right = right == NULL ? 0 : right->value;
	start = left == NULL ? right->start : left->start;
	end = right == NULL ? left->end : right->end;

	// This line is the one that defines the usecase of the
	// range tree
	node* father = make_node(v_left + v_right, start, end);
	father->left = left;
	father->right = right;

	if(left != NULL)
		left->father = father;
	if(right != NULL)
		right->father = father;
	return father;
}

node* build_tree(node** nodes, int size)
{
	if(size == 0)
		return NULL;
	if(size == 1)
		return nodes[0];
	if(size == 2)
		return build_father(nodes[0], nodes[1]);
	return build_father(build_tree(nodes, size / 2), build_tree(nodes + size / 2, size - size / 2));
}

int range_value(node* root, int start, int end)
{
	int left, right;
	if(start == root->start && end == root->end)
		return root->value;
	if(start >= end)
		return 0;

	left = root->left == NULL ? 0 : range_value(root->left, start, root->left->end);
	right = root->right == NULL ? 0 : range_value(root->right, root->right->start, end);
	return left + right;
}

void change_node_value(node* n, int value)
{
	int old_value = n->value;
	n->value = value;
	if(n->father != NULL)
		change_node_value(n->father, n->father->value - old_value + value);
}
