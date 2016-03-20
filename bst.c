#include "bst.h"



/********************************************//**
  * \function returns an integer to tell you if the left value is greater then, less then, or equal to the right value.
        _used to compare node values
  * \pre: none
  * \post: none
  * \left left node value
  * \right: right node value
  * \rules:
  *     if left < right return -1
  *     if left > right return 1
  *     if left = right return 0
  * \return:integer value is returned according to rules:
***********************************************/
int compareValues(TYPE left, TYPE right) {
    int reVal;

    if(left<right){
        reVal = -1;
    } else if(left > right){
        reVal = 1;
    } else{ // left == right
        reVal = 0;
    }

    return reVal;//done
}

/********************************************//**
 * \initBSTree: function to initialize the binary search tree.
 *
 * \param1: BST tree
 * \pre: tree is not null
 * \post: tree size is 0 && root != NULL
 * \return: nothing
 *
 ***********************************************/

void initBSTree(struct BSTree *tree) {
    assert(tree != NULL);
	tree->cnt  = 0;
	tree->root = NULL;


	return;//done
}

/********************************************//**
 * \newBSTree: function to create a binary search tree.
 *
 * \params: none
 * \pre: none
 * \return: returns an empty tree
 * \functionCall: initBSTree
 *
 ***********************************************/

struct BSTree* newBSTree() {
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != NULL);

	initBSTree(tree);
	return tree;//done
}

/*
	freeBSTree: function to clear the nodes of a binary search tree
	param: tree a binary search tree
	pre: tree not null
	post: the nodes of the tree are deallocated, as well as the tree itself
	tree->root = 0;
	tree->cnt = 0
	nodes are removed by _freeNodes
 */
void freeBSTree(struct BSTree *tree) {
    assert(tree != NULL);
	_freeNodes(tree->root);
	tree->root = NULL;
	tree->cnt  = 0;
	free(tree);
	printf("tree freed \n");

	return;//done
}//done

/*
	_freeBST: function to free the nodes of a binary search tree
	param: node - the root node of the tree to be freed
	pre: node is not null
	post: node and all descendants are deallocated
*/
void _freeNodes(struct Node *node) {
	if (node != NULL) {
		_freeNodes(node->left);
		_freeNodes(node->right);
		free(node);
	}

	return;//done
}

/*
	isEmptyBSTree: function to determine if  a binary search tree is empty.
	param: tree the binary search tree
	pre:  tree is not null
	return: return 1 if the tree is empty, otherwise return 0
 */
int isEmptyBSTree(struct BSTree *tree) {
    /* FIX ME */
    int testVal;
    if(tree->cnt > 0){
        testVal = 0;
    } else{
        testVal = 1;
    }

    return testVal;//done
}

/*
	sizeBSTree: function to determine the size of a binary search tree
	param: tree - the BST
	pre: tree is not null
	return: return the size of the tree
*/
int sizeBSTree(struct BSTree *tree) {
    /* FIX ME */
    int reValue;

    assert(tree != NULL);

    reValue = tree->cnt;

    return reValue;//done
}

/*
	addBSTree: function to add a value to the binary search tree
	param1: tree - the binary search tree
	param2: val	- the value to be added to the tree
	pre: tree is not null
	post: cnt is incremented
	_addNode handles the actual add
 */
void addBSTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);

    printf("Adding %.1f \n", val);
    tree->root = _addNode(tree->root, val);
    tree->cnt++;

    return;//done
}

/*
	_addNode: function to add a value to the binary search tree
	param1: curr - the current node
	param2: val	- the value to be added to the tree
	pre: curr is not null
	post:  tree size incremented
	post: tree now contains val
 */
struct Node *_addNode(struct Node *curr, TYPE val) {
    /* FIX ME */
    if(curr==NULL) {
        struct Node *temp;
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp -> val = val;
        temp -> left = temp -> right = NULL;
        return temp;
    }

    if(val > (curr->val)) {
        curr->right = _addNode(curr->right,val);
    }
    else if(val <= (curr->val)) {
        curr->left = _addNode(curr->left,val);

    }

    return curr;//done
}

/*
	containsBSTree: function to determine if the binary search tree contains an element - calls _contains
	param1: tree the binary search tree
	param2: val	- the value to search for in the tree
	pre: tree is not null
	pre: val is not null
	post: return 1 if the tree contains the value, otherwise return 0
 */
int containsBSTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);

	return _containsNode(tree->root, val);//done
}

/*
	_contains: function to find a value from the binary search tree
	param1: curr - the current node
	param2: val	- the value to be found
	pre: curr is not null
	pre: val is not null
	post: return 1 if found, otherwise return 0
*/
int _containsNode(struct Node *curr, TYPE val) {
    /* FIX ME */
    int reVal;

    if(curr==NULL){
        reVal = 0;
    }
    else if(val > curr->val){
        reVal = _containsNode(curr->right, val);
    }
    else if(val < curr->val){
        reVal=_containsNode(curr->left, val);
    }
    else if(val == curr -> val){
        reVal = 1;
    }



	return reVal;//done
}



/*
	removeBSTree: function to remove a value from the binary search tree - calls _removeNode
	param1: tree - the binary search tree
	param2: val	- the value to be removed from the tree
	pre: tree is not null
	pre: val is not null
	pre: val is in the tree
	post: tree size is reduced by 1
*/
void removeNodeFromTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	} else {
        printf("node is not contained in the tree \n");
	}

	return;//done
}

/*
 * _removeNode: remove a node from the tree - recursive implementation
 * param1: curr - the current node
 * param1: val - the value to be removed from the tree
 * pre: val is in the tree
 * pre: curr is not null
 * pre: val is not null
	post: descendant of curr containing val is removed from the tree
	HINT - There are 3 cases: the node is a leaf, the node has only one subtree, the node has two subtrees
	use leftmost to get the value (when needed) and removeLeftmost (when needed).
 */
struct Node *_removeNode(struct Node *curr, TYPE val) {
	/**< base case */
    if (curr == NULL){
        return curr;
    }

    /**< If the val to be deleted is smaller than the curr-> val it is on the left side */
    if (val < curr->val){
        curr->left = _removeNode(curr->left, val);
    }

    /**< If the val to be deleted is greater than the curr->val then it is on the right side */
    else if (val > curr->val){
        curr->right = _removeNode(curr->right, val);
    }

    /**< if val is same as curr->val, then This is the node to be deleted */
    else{
        struct Node*temp, *currnt;
        /**< node with only one child or no child */
        if (curr->left == NULL){
            temp=curr->right;
            free(curr);
            return temp;
        }
        else if (curr->right == NULL){
            temp = curr->left;
            free(curr);
            return temp;
        }

        /**< node with two children */

        currnt = curr->right;
        while (currnt->left != NULL){
            currnt = currnt->left;
        }
        printf("While loop ended!\n");

        temp = currnt;

        /**< Copy back to curr */
        curr->val = temp->val;

        /**< Delete the successors */
        curr->right = _removeNode(curr->right, temp->val);
    }

    return curr;/**< done */
}

/*
 * leftMostValue: helper function to find the left most child of a node - iterative implementation
 * param: curr the current node
 * pre: curr is not null
 * post: return the value of the left most child of curr
*/
TYPE _leftMostValue(struct Node *curr) {
	while(curr->left != NULL) {
        curr = curr->left;
    }

	return curr->val;//done
}

/*
	_removeLeftMost: helper function to remove the left most child of a node - iterative implementation
	param: curr - the current node
	pre: curr is not null
	post: the leftmost node of curr is not in the tree
 */
void _removeLeftMost(struct Node *curr) {
    if(curr->left == NULL) {
        printf("left subtree is empty \n");
        return;
    }
    struct Node *curr_parent = curr;
	while(curr->left != NULL) {
            curr_parent = curr;
            curr = curr->left;
    }
    curr_parent->left = NULL;
    free(curr);
    printf("leftmost node removed \n");

    return;//done
}


/*
	rightMostValue: helper function to find the right most child of a node - iterative implementation
	param: curr the current node
	pre: curr is not null
	post: return the value of the right most child of curr
*/
TYPE _rightMostValue(struct Node *curr) {
	while(curr->right != NULL) {
        curr = curr->right;
    }

	return curr->val;//done
}

/*
	_removeRightMost: helper function to remove the right most child of a node - iterative implementation
	param: curr - the current node
	pre: curr is not null
	post: the rightmost node of curr is not in the tree
 */
void _removeRightMost(struct Node *curr) {
    if(curr->right == NULL) {
        printf("right subtree is empty \n");
        return;
    }
    struct Node *curr_parent = curr;
	while(curr->right != NULL) {
            curr_parent = curr;
            curr = curr->right;
    }
    curr_parent->right = NULL;
    free(curr);
    printf("leftmost node removed \n");

    return;//done
}


/*
    inorderTraversal: inorder traversal of tree left-node-right
    param: curr - the current node
    pre: curr is not null
    post: in-order traversal s printed
*/
void inorderTraversal(struct Node *curr) {
    if (curr != NULL){
        inorderTraversal(curr->left);
        printf("%f \n", curr->val);
        inorderTraversal(curr->right);
    }

    return;//done
}

/*
    preorderTraversal: inorder traversal of tree node-left-right
    param: curr - the current node
    pre: curr is not null
    post: pre-order traversal s printed
*/
void preorderTraversal(struct Node *curr) {
    if (curr != NULL){
        printf("%f \n", curr->val);
        inorderTraversal(curr->left);
        inorderTraversal(curr->right);
    }

    return;//done
}

/*
    postorderTraversal: post-order traversal of tree left-right-node
    param: curr - the current node
    pre: curr is not null
    post: post-order traversal s printed
*/
void postorderTraversal(struct Node *curr) {
    if (curr != NULL){
        inorderTraversal(curr->left);
        inorderTraversal(curr->right);
        printf("%f \n", curr->val);
    }

    return;//done
}
