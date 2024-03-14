#include "Node.h"

#ifndef HELPERS_H
#define HELPERS_H

using namespace std;

void printAllFingerTables();

void printLocalTableForAllNodes();

void printLookupResultsForAllKeysOnNode(Node* node);

void printNodePath(vector<Node*>& path);

void printLocalTable(Node* node);

void printNodeFingerTable(Node* node);

extern int M;

extern map<int, Node*> nodeMap;
extern vector<int> keysVector;

#endif
