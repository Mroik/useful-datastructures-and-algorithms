#include <stdlib.h>

typedef struct lnode_r {
	struct node_r* value;
	struct lnode_r* next;
} lnode;

typedef struct node_r {
	int value;
	lnode* children;
} node;

lnode* make_lnode(node* value)
{
	lnode* new_node = malloc(sizeof(lnode));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

node* make_node(int value)
{
	node* new_node = malloc(sizeof(node));
	new_node->value = value;
	new_node->children = NULL;
	return new_node;
}

int top(node* root)
{
	return root->value;
}

void add_children(lnode* root, node* child)
{
	if(root->next == NULL)
		root->next = make_lnode(child);
	else
		add_children(root->next, child);
}

node* meld(node* h1, node* h2)
{
	if(h1 == NULL && h2 == NULL)
		return NULL;
	if(h1 == NULL)
		return h2;
	if(h2 == NULL)
		return h1;
	if(h1->value < h2->value)
	{
		if(h1->children == NULL)
			h1->children = make_lnode(h2);
		else
			add_children(h1->children, h2);
		return h1;
	}
	else
	{
		if(h2->children == NULL)
			h2->children = make_lnode(h1);
		else
			add_children(h2->children, h1);
		return h2;
	}
}

node* insert(node* root, int value)
{
	node* new_node = make_node(value);
	if(root == NULL)
		return new_node;
	return meld(root, new_node);
}

node* merge_pairs(lnode* root)
{
	if(root == NULL)
		return NULL;
	if(root->next == NULL)
		return root->value;
	meld(meld(root->value, root->next->value), merge_pairs(root->next->next));
}

node* pop(node* root)
{
	if(root == NULL)
		return NULL;
	lnode* temp = root->children;
	free(root);
	return merge_pairs(temp);
}
