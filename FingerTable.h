#ifndef FINGERTABLE_H
#define FINGERTABLE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <utility>
using namespace std;

//Header file for FingerTable class

class Node;

struct Finger {
	int interval_st, interval_end;
	Node* next_node;
};

class FingerTable{
	public:
		FingerTable();
		FingerTable(Node* node);

		vector<Finger> fingerTable;

		void setNextNode(int index, Node* next_node);
		Node* getNextNode(int index);
		void print();
};

#endif
