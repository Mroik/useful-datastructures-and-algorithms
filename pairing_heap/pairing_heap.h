typedef struct lnode_r {
	struct node_r* value;
	struct lnode_r* next;
} lnode;

typedef struct node_r {
	int value;
	lnode* children;
} node;

node* make_node(int value);
int top(node* root);
node* insert(node* root, int value);
node* pop(node* root);
node* meld(node* h1, node* h2);
