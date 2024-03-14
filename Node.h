#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include "FingerTable.h"
using namespace std;

//Node header file gives the definition of Node and FingerTable

class Node {
    public:

        Node(int id);

        int id;
        FingerTable fingerTable;
        std::map<int, int> localTable;
        Node* predecessor;

        void join(Node* node);
        int find(int key);
        void insert(int key, int value = -1);
        void remove(int key);
        Node* locateSuccessorInRing(int key);
        Node* closestPrecedingNode(int key);
        Node* locateSuccessorInRingAndTrackNodePath(int key, vector<Node*>& path);
        Node* closestPrecedingNodeAndTrackNodePath(int key, vector<Node*>& path);
        void updateFingerTableForNode(Node* node, int index);
        void moveKeysFromSuccessor();
        Node* getPredecessor();
        Node* getSuccessor();
        void setPredecessor(Node* node);
};

#endif
