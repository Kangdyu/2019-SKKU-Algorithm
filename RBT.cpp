// Red black tree
#include<stdio.h>
#include<time.h>
#include "RBT.h"

// make new node
Node* RBT::NewNode(int key)
{
	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));

	temp->key = key;

	temp->left = nil;
	temp->right = nil;
	temp->parent = nil;
	temp->red = 1;

	return temp;
}

// search node 
Node* RBT::TREE_SEARCH(Node* root, int key) {
	Node* cur = root;
	while (cur != nil) {
		if (cur->key < key) {
			cur = cur->right;
		}
		else if (cur->key > key) {
			cur = cur->left;
		}
		else {
			return cur;
		}
	}
	return cur;
}

// find successor of specific node
Node* RBT::SUCCESSOR(Node* cur) {
	if (cur->right == nil) {
		Node* y = cur->parent;
		while (y != nil && cur == y->right)
		{
			cur = y;
			y = y->parent;
		}
		return y;
	}
	else {
		cur = cur->right;
		while (cur->left != nil) {
			cur = cur->left;
		}
		return cur;
	}
}

// left rotation of tree
void RBT::left_rotate(Node** root, Node* x)
{
	struct Node* y = x->right;
	x->right = y->left;

	if (y->left != nil) {
		y->left->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == nil) {
		*root = y;
	}
	else {
		if (x == x->parent->left) {
			x->parent->left = y;

		}
		else {
			x->parent->right = y;
		}
	}

	y->left = x;
	x->parent = y;
}

// right rotation of tree
void RBT::right_rotate(Node** root, Node* x)
{
	struct Node* y = x->left;
	x->left = y->right;

	if (y->right != nil) {
		y->right->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == nil) {
		*root = y;
	}
	else {
		if (x == x->parent->right) {
			x->parent->right = y;

		}
		else {
			x->parent->left = y;
		}
	}

	y->right = x;
	x->parent = y;
}

// Red-Black tree insert fixup function
void RBT::INSERT_FIXUP(Node** root, Node* z) {

	struct Node* y = NULL;
	while ((z->parent)->red == 1) {
		if (z->parent == (z->parent->parent)->left) {
			y = (z->parent->parent)->right;
			if (y->red == 1) {
				(z->parent)->red = 0;
				y->red = 0;
				(z->parent->parent)->red = 1;
				z = (z->parent->parent);
			}
			else {
				if (z == (z->parent)->right) {
					z = z->parent;
					left_rotate(root, z);
				}
				(z->parent)->red = 0;
				z->parent->parent->red = 1;
				right_rotate(root, z->parent->parent);
			}
		}
		else {
			y = z->parent->parent->left;
			if (y->red == 1) {
				z->parent->red = 0;
				y->red = 0;
				z->parent->parent->red = 1;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(root, z);
				}
				z->parent->red = 0;
				z->parent->parent->red = 1;
				left_rotate(root, z->parent->parent);
			}
		}
	}
	(*root)->red = 0;
}

// this function used at first 500 input, same as TREE_INSERT, but not print # of nodes and height.
void RBT::TREE_INSERT_INIT(Node** root, Node** node)
{
	bool AlreadyExist = false;

	struct Node* z = *node;
	struct Node* y = nil;
	struct Node* x = *root;

	int key = z->key;

	while (x != nil) {
		y = x;

		if (z->key < x->key) {
			x = x->left;
		}
		else if (z->key > x->key) {
			x = x->right;
		}
		else {
			AlreadyExist = true;
			break;
		}
	}

	if (!AlreadyExist) {
		z->parent = y;

		if (y == nil) {
			*root = z;
		}
		else {
			if (z->key < y->key) {
				y->left = z;
			}
			else {
				y->right = z;
			}
		}

		z->left = nil;
		z->right = nil;
		z->red = 1;

		INSERT_FIXUP(root, z);
	}
	else {
		printf("Redervation Number %d is already Reserved!\n", key);
	}
}

// Insert node
void RBT::TREE_INSERT(Node** root, Node** node)
{
	bool AlreadyExist = false;

	struct Node* z = *node;
	struct Node* y = nil;
	struct Node* x = *root;

	int key = z->key;

	while (x != nil) {
		y = x;

		if (z->key < x->key) {
			x = x->left;
		}
		else if (z->key > x->key) {
			x = x->right;
		}
		else {
			AlreadyExist = true;
			break;
		}
	}

	if (!AlreadyExist) {
		z->parent = y;

		if (y == nil) {
			*root = z;
		}
		else {
			if (z->key < y->key) {
				y->left = z;
			}
			else {
				y->right = z;
			}
		}

		z->left = nil;
		z->right = nil;
		z->red = 1;

		INSERT_FIXUP(root, z);
	}
	else {
		printf("Redervation Number %d is already Reserved!\n", key);
	}
	print_number_and_height(root);
}

// Rek-Balck tree delete fixup function
void RBT::DELETE_FIXUP(Node** root, Node* x) {

	struct Node* w; // siblings

	while (x != *root && x->red == 0) {
		if (x == x->parent->left) {
			w = x->parent->right;

			//case 1
			if (w->red == 1) {
				w->red = 0;
				x->parent->red = 1;
				left_rotate(root, x->parent);
				w = x->parent->right;
			}

			//case 2
			if (w->left->red == 0 && w->right->red == 0) {
				w->red = 1;
				x = x->parent;
			}
			//case 3
			else if (w->right->red == 0) {
				w->left->red = 0;
				w->red = 1;
				right_rotate(root, w);
				w = x->parent->right;
			}
			//case 4
			w->red = x->parent->red;
			x->parent->red = 0;
			w->right->red = 0;
			left_rotate(root, x->parent);
			x = *root;
		}
		else {
			w = x->parent->left;

			//case 1
			if (w->red == 1) {
				w->red = 0;
				x->parent->red = 1;
				right_rotate(root, x->parent);
				w = x->parent->left;
			}

			//case 2
			if (w->right->red == 0 && w->left->red == 0) {
				w->red = 1;
				x = x->parent;
			}
			//case 3
			else if (w->left->red == 0) {
				w->right->red = 0;
				w->red = 1;
				left_rotate(root, w);
				w = x->parent->left;
			}
			//case 4
			w->red = x->parent->red;
			x->parent->red = 0;
			w->left->red = 0;
			right_rotate(root, x->parent);
			x = *root;
		}
	}

	x->red = 0;
}

// Delete node
void RBT::TREE_DELETE(Node** root, int key) {

	struct Node* z = TREE_SEARCH(*root, key);

	if (z != nil) {
		struct Node* y;
		struct Node* x;

		if (z->left == nil || z->right == nil) {
			y = z;
		}
		else {
			y = SUCCESSOR(z);
		}

		if (y->left != nil) {
			x = y->left;
		}
		else {
			x = y->right;
		}

		x->parent = y->parent;

		if (y->parent == nil) {
			*root = x;
		}
		else {
			if (y == y->parent->left) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}

		if (y != z) {
			z->key = y->key;
		}
		if (y->red == 0) {
			DELETE_FIXUP(root, x);
		}
	}
	else {
		printf("Redervation Number %d is not Reserved!\n", key);
	}
	print_number_and_height(root);
}

// print number of nodes, and highest height of tree
void RBT::print_number_and_height(Node** root) {
	number_of_nodes = 0;
	highest = 0;

	traversal(*root, 0);

	printf("Number of Nodes:%d, Height of the tree:%d\n", number_of_nodes, highest);
}

// this function used at print_number_and_height function
void RBT::traversal(Node* root, int height) {
	if (root != nil)
	{
		number_of_nodes++;

		if (highest < height) {
			highest = height;
		}

		traversal(root->left, height + 1);
		traversal(root->right, height + 1);
	}
}

/*
int main() {

	//�׽�Ʈ�� ���
	Node* node = NewNode(10);

	//Red Black Tree �����ϴ� ���
	RBT rbt;

	//Insert�ϴ� ��� -> ���⼭�� ��带 ��°�� �־�� �ϱ⿡ Parameter�� Delete�� �ٸ�.
	rbt.TREE_INSERT(&rbt.root, &node);

	//Delete�ϴ� ��� -> ���⼭�� Key���� �߿��ϱ⿡ Key���� ����
	rbt.TREE_DELETE(&rbt.root, 10);
}
*/

