// Manage world map with graph
#ifndef RBT_H
#define RBT_H

#include "Path.h"
#include<stdlib.h>

// node which save reservation information
struct  Node
{
	// left, right, parent node pointer
	struct Node* left = NULL;
	struct Node* right = NULL;
	struct Node* parent = NULL;

	// array which save seat level
	int seat[26];

	// person's name
	char name[3];
	// source(start) city
	char sour;
	// destination city
	char dest;

	// reservation number
	int key = -1;

	// if red = 1, node is red, red = 0, node is black
	int red = 1;

	// sum of ticket price
	int ticket_price = 0;

	// sum of flight time
	int flight_time = 0;

	// departure time, and date
	int departure_time, departure_date;
	// arrival time, and date
	int arrival_time, arrival_date;

	// this pointer save path information
	Path path;
};

// Red-Black tree class
class RBT {

	// this variable will save the highest height of tree
	int highest = 0;
	// this variable will save the number of nodes in tree
	int number_of_nodes = 0;

public:

	struct Node *nil = (struct Node*)malloc(sizeof(struct Node));
	struct Node *root = nil;

	Node* NewNode(int key);

	// search node 
	Node* TREE_SEARCH(Node* root, int key);

	// find successor of specific node
	Node* SUCCESSOR(Node* cur);

	// left rotation of tree
	void left_rotate(Node** root, Node* x);

	// right rotation of tree
	void right_rotate(Node** root, Node* x);

	// Red-Black tree insert fixup function
	void INSERT_FIXUP(Node** root, Node* z);

	// this function used at first 500 input, same as TREE_INSERT, but not print # of nodes and height.
	void TREE_INSERT_INIT(Node** root, Node** node);

	// Insert node
	void TREE_INSERT(Node** root, Node** node);

	// Rek-Balck tree delete fixup function
	void DELETE_FIXUP(Node** root, Node* x);

	// Delete node
	void TREE_DELETE(Node** root, int key);

	// print number of nodes, and highest height of tree
	void print_number_and_height(Node** root);

	// this function used at print_number_and_height function
	void traversal(Node* root, int height);
};

#endif