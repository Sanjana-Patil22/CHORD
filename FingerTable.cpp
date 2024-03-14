
#include "FingerTable.h"
#include "Node.h"
#include "Helpers.h"
#include <math.h>
#include <vector>
#include <iostream>

FingerTable::FingerTable(Node* node){

	// Initialize the table
	fingerTable.reserve(M+1);

	for(int i = 1; i <= M; i++){
		fingerTable[i] = {
			(node->id + int(pow(2, i-1)) ) % int(pow(2, M)),
			(node->id + int(pow(2, i)) ) % int(pow(2, M)),
			node
		};
	}
}

void FingerTable::setNextNode(int index, Node* next_node){

	// Set the next node in the finger table
	fingerTable[index].next_node = next_node;
}

Node* FingerTable::getNextNode(int index) {

	// Get the next node in the finger table
	return fingerTable[index].next_node;
}

// Constructor
FingerTable::FingerTable(){
	fingerTable.reserve(M+1);
}

void FingerTable::print(){

	// Print the finger table
	for(int i = 1; i <= M; i++){
		string row = "";
		row += " | k = ";
		row += to_string(i);
		row += " [";
		row += to_string(fingerTable[i].interval_st);
		row += ", ";
		row += to_string(fingerTable[i].interval_end);
		row += ") \t";
		row += "succ. = ";
		row += to_string(getNextNode(i)->id);
		row += "  |";
		cout << row << endl;
	}
};
