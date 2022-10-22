#include <stdlib.h>

typedef struct node_r {
	int value;
	struct node_r* next;
	struct node_r* children;
} node;

node* make_node(int value)
{
	node* new_node = malloc(sizeof(node));
	new_node->value = value;
	new_node->next = NULL;
	new_node->children = NULL;
	return new_node;
}

int top(node* root)
{
	return root->value;
}

void add_sibling(node* root, node* sibling)
{
	if (root->next == NULL)
		root->next = sibling;
	else
		add_sibling(root->next, sibling);
}

node* meld(node* h1, node* h2)
{
	if (h1 == NULL && h2 == NULL)
		return NULL;
	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h1;

	if (h1->value < h2->value) {
		if (h1->children == NULL)
			h1->children = h2;
		else
			add_sibling(h1->children, h2);
		return h1;
	} else {
		if (h2->children == NULL)
			h2->children = h1;
		else
			add_sibling(h2->children, h1);
		return h2;
	}
}

node* insert(node* root, int value)
{
	node* new_node = make_node(value);
	if (root == NULL)
		return new_node;
	return meld(root, new_node);
}

node* merge_pairs(node* root)
{
	if (root == NULL)
		return NULL;
	if (root->next == NULL)
		return root;

	node* h1 = root;
	node* h2 = root->next;
	node* rest = root->next->next;

	h1->next = NULL;
	h2->next = NULL;
	return meld(meld(h1, h2), merge_pairs(rest));
}

node* pop(node* root)
{
	if (root == NULL)
		return NULL;
	node* temp = root->children;
	free(root);
	return merge_pairs(temp);
}
