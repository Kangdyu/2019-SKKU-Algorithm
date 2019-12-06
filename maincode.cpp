#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "RBT.h"

RBT rbt;
TimeTable t;
Graph g;

void make_res(Node* node) {
	// ask for name, source city, destination city and departure date
	printf("enter your name : ");
	scanf("%s", &node->name);

	printf("\nenter your source city : ");
	scanf(" %c", &node->sour);

	printf("\nenter your destination city : ");
	scanf(" %c", &node->dest);

	printf("\nenter date : ");
	scanf(" %d", &node->departure_date);

	// insert reservation info for RBT
	rbt.TREE_INSERT(&rbt.root, &node);
	
	// find path
	node->path = g.find_path(node->sour, node->dest, node->departure_date, t);

	// select seat level and calculate ticket price
	node->ticket_price = 0;
	int loopnum = node->path.get_size();
	while (loopnum > 0) {
		printf("select your seat level");
		printf("1 : prestige class  2 : business class  3 : economy class\n");
		int level = 0;
		scanf("%d", &level);

		switch (level) {
		case 1:
			printf("thank you for select prestige class, ticket price for prestige class is ");
			node->ticket_price += 1;
			break;
		case 2:
			printf("thank you for select business class, ticket price for business class is ");
			node->ticket_price += 2;
			break;
		case 3:
			printf("thank you for select economy class, ticket price for economy class is ");
			node->ticket_price += 3;
			break;
		default:
			printf("wrong number\n");
			loopnum++;
			continue;
		}

		loopnum--;
	}

	// print reservation result
	printf("reservation success, your reservation number is %d\n", node->key);
	printf("source : %c, destination : %c, departure date : %d, ticket price : %d\n", node->sour, node->dest, node->departure_date, node->ticket_price);
}

void delete_res(RBT rbt) {
	// delete reservation
	int delete_key;
	printf("enter your reservation number : ");
	scanf("%d", &delete_key);
	rbt.TREE_DELETE(&rbt.root, delete_key);
}

int main() {

	int src_rand = 0;
	int dest_rand = 0;
	int fname = 0;
	int sname = 0;
	//srand(time(NULL));
	
	// building timetable
	t.random_generate();
	// building graph
	g.random_generate(&t);

	// building initial RBT
	int keynum = 1;
	while (keynum <= 500) {
		Node* node = rbt.NewNode(keynum);
		// random name
		fname = rand() % 26;
		sname = rand() % 26;
		node->name[0] = 'a' + fname;
		node->name[1] = 'a' + sname;

		// random date
		node->departure_date = rand() % 31;
		node->departure_date += 1;

		// random sour
		src_rand = rand() % 26;
		node->sour = 'a' + src_rand;

		// random dest
		dest_rand = rand() % 26;
		node->dest = 'a' + dest_rand;

		rbt.TREE_INSERT_INIT(&rbt.root, &node);
		keynum = keynum + 1;
	}
	
	// asking what to do
	while (1) {
		int state = 1; // 1 : make reservation    2 : delete reservation   0 : exit
		printf("1 : make reservation\n2 : delete reservation\n0 : exit program\n");
		scanf("%d", &state);

		if (state == 0) {
			// exit program
			break;
		}
		else if (state == 1) {
			// make reservation
			Node* resnode = rbt.NewNode(keynum);
			make_res(resnode);
			keynum++;
		}
		else if (state == 2) {
			// delete reservation
			delete_res(rbt);
		}
		else {
			printf("--- input error ---");
		}
	}
}