#include "Node.h"
#include <math.h>
#include "Helpers.h"
#include <iostream>
#include "FingerTable.h"

Node* Node::getPredecessor(){
    return predecessor;
}

void Node::setPredecessor(Node* node){
    predecessor = node;
}

Node* Node::getSuccessor(){
    return fingerTable.getNextNode(1);
}

int Node::find(int key){

    // If the key is in the local table, return its value

    vector<Node*> path;
    Node* node = locateSuccessorInRingAndTrackNodePath(key, path);

    int value = node->localTable[key];

    cout << "Look-up result of key " << key << " from node " << this->id << " with path ";
    printNodePath(path);
    cout << "value is " << (value == -1 ? "None" : to_string(value)) << endl;

    return value;
}

void Node::insert(int key, int value){

    // Insert key and value into the local table

    Node* node = locateSuccessorInRing(key);

    node->localTable[key] = value;
    keysVector.push_back(key);
}

void Node::remove(int key){

    // Remove key from the local table

    Node* node = locateSuccessorInRing(key);
    node->localTable.erase(key);
}

Node* Node::locateSuccessorInRing(int key){

    // Find the node that has the smallest ID greater than or equal to the given key

    if(key == this->id){
        return this;
    }

    Node* cPrecedingNode = closestPrecedingNode(key);
    return cPrecedingNode->getSuccessor();
}

Node* Node::locateSuccessorInRingAndTrackNodePath(int key, vector<Node*>& path){

    // Find the node that has the smallest ID greater than or equal to the given key

    path.push_back(this);

    if(key == this->id){
        return this;
    }

    Node* cPrecedingNode= closestPrecedingNodeAndTrackNodePath(key, path);
    path.push_back(cPrecedingNode->getSuccessor());
    return cPrecedingNode->getSuccessor();
}

Node* Node::closestPrecedingNode(int key){

    // Find the node that has the smallest ID greater than or equal to the given key

    Node* closestPrecedingNode= this;

    for(int i = M; i >= 1; i--){
        if (closestPrecedingNode->fingerTable.getNextNode(i)->id == this->id) {
            continue;
        }

        if(key >= closestPrecedingNode->id){
            if (closestPrecedingNode->fingerTable.getNextNode(i)->id <= key &&
                closestPrecedingNode->fingerTable.getNextNode(i)->id >= closestPrecedingNode->id)
                closestPrecedingNode = closestPrecedingNode->fingerTable.getNextNode(i);
        }
        else if (closestPrecedingNode->fingerTable.getNextNode(i)->id <= key ||
            closestPrecedingNode->fingerTable.getNextNode(i)->id >= closestPrecedingNode->id) {
                closestPrecedingNode = closestPrecedingNode->fingerTable.getNextNode(i);
        }
    }

    return closestPrecedingNode;
}


Node* Node::closestPrecedingNodeAndTrackNodePath(int key, vector<Node*>& path){

    // Find the node that has the smallest ID greater than or equal to the given key

    Node* closestPrecedingNode= this;

    for(int i = M; i>=1; i--){
        if (closestPrecedingNode->fingerTable.getNextNode(i)->id == this->id) {
            continue;
        }

        if(key >= closestPrecedingNode->id){
            if (closestPrecedingNode->fingerTable.getNextNode(i)->id <= key &&
                closestPrecedingNode->fingerTable.getNextNode(i)->id >= closestPrecedingNode->id)
                closestPrecedingNode = closestPrecedingNode->fingerTable.getNextNode(i);
        }
        else if (closestPrecedingNode->fingerTable.getNextNode(i)->id <= key ||
            closestPrecedingNode->fingerTable.getNextNode(i)->id >= closestPrecedingNode->id) {
                closestPrecedingNode = closestPrecedingNode->fingerTable.getNextNode(i);
        }
    }

    path.push_back(closestPrecedingNode);
    return closestPrecedingNode;
}

void Node::join(Node* node){

    // Set the successor of this node to be the successor of the given node

    nodeMap[id] = this;

    if (node == NULL){
        setPredecessor(this);
        return;
    }

    Node* successor = node->locateSuccessorInRing(this->fingerTable.fingerTable[1].interval_st);

    this->fingerTable.setNextNode(1, successor);
    setPredecessor(successor->getPredecessor());
    successor->setPredecessor(this);

    for(int i = 2; i <= M; i++){
        Node* successor= node->locateSuccessorInRing(this->fingerTable.fingerTable[i].interval_st);
        this->fingerTable.setNextNode(i, successor);
    }

    for(int i = 1; i <= M; i++){
        int prevKey = this->id - pow(2, i-1);
        if (prevKey < 0) {
            prevKey = pow(2, M) - prevKey;
        }

        Node* prevNode = closestPrecedingNode(prevKey);
        prevNode->updateFingerTableForNode(this, i);
    }

    moveKeysFromSuccessor();
}

void Node::updateFingerTableForNode(Node* node, int index){

    // Update the finger table of this node so that it points to the given node

    if (node == this) {
        return;
    }

    if (this->id < fingerTable.fingerTable[index].next_node->id) {
        if (node->id < fingerTable.fingerTable[index].next_node->id && node->id >= this->id) {
            this->fingerTable.setNextNode(index, node);
            getPredecessor()->updateFingerTableForNode(node, index);
        }
    } else if (node->id < fingerTable.fingerTable[index].next_node->id || node->id >= this->id) {
        this->fingerTable.setNextNode(index, node);
        getPredecessor()->updateFingerTableForNode(node, index);
    }
}

void Node::moveKeysFromSuccessor(){

    // Migrate keys from the successor to this node

    Node* successor = getSuccessor();
    if (successor == this) {
        return;
    }

    std::map<int, int> successorLocalTable= successor->localTable;


    for (auto it = successorLocalTable.begin(); it != successorLocalTable.end(); ++it){
        if(it->first <= this->id){
            this->localTable[it->first]= it->second;
            cout << "migrate key " << it->first << " from node " << successor->id << " to node " << this->id << endl;
        }
    }

    for (auto it = successorLocalTable.begin(); it != successorLocalTable.end(); ++it){
        if(it->first <= this->id){
            successor->localTable.erase(it->first);
        }
    }
}

Node::Node(int newNodeId) {
    id = newNodeId % int(pow(2, M));
    fingerTable = FingerTable(this);
    predecessor = NULL;
}
