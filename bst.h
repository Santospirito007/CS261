#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

/* Defines the type to be stored in the data structure */
# define TYPE double

struct Node {
	TYPE val;
	struct Node *left;//left node of tree
	struct Node *right;//right node of tree
};

/* BST definition */
struct BSTree {
	struct Node *root;//root of tree
	int cnt; //size of tree
};


int compareValues(TYPE left, TYPE right);
void initBSTree(struct BSTree *tree);
struct BSTree *newBSTree();
void freeBSTree(struct BSTree *tree);
void _freeNodes(struct Node *node);
int isEmptyBSTree(struct BSTree *tree);
int sizeBSTree(struct BSTree *tree);

void addBSTree(struct BSTree *tree, TYPE val);
struct Node *_addNode(struct Node *curr, TYPE val);

int containsBSTree(struct BSTree *tree, TYPE val);
int _containsNode(struct Node *curr, TYPE val);

void removeNodeFromTree(struct BSTree *tree, TYPE val);
struct Node *_removeNode(struct Node *curr, TYPE val);
TYPE _leftMostValue(struct Node *curr);
void _removeLeftMost(struct Node *curr);

TYPE _rightMostValue(struct Node *curr);
void _removeRightMost(struct Node *curr);

void inorderTraversal(struct Node *curr);
void preorderTraversal(struct Node *curr);
void postorderTraversal(struct Node *curr);

