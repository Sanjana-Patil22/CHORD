
#include <iostream>
#include <stdint.h>
#include "Helpers.h"
#include <map>

int M = 8;

void printAllFingerTables() {

    for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        printNodeFingerTable(it->second);
    }
}

void printLocalTableForAllNodes() {

    for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        printLocalTable(it->second);
    }
}

void printLookupResultsForAllKeysOnNode(Node* node) {

    cout << "------------------------------node " << node->id << "-----------------------------------" << endl;
    for (auto key: keysVector) {
        node->find(key);
    }
}

void printNodePath(vector<Node*>& path){

    cout << "[";
    for (auto i = 0; i < path.size(); i++) {
        cout << path[i]->id;
        if (i != path.size() -1)
            cout << ", ";
    }
    cout << "] ";
}

void printLocalTable(Node* node){

    cout << "----------" << "Node id: " << node->id << "----------" << endl << endl;
    std::map<int, int> localTableMap= node->localTable;

    string row = "";
    for (auto it = localTableMap.begin(); it != localTableMap.end(); ++it){
        row += to_string(it->first) + ": " + (it->second == -1 ? "None" : to_string(it->second));
        if (std::next(it) != localTableMap.end()) {
            row += ", ";
        }
    }

    cout << "{" << row << "}" << endl;
}

void printNodeFingerTable(Node* node){
    cout << "----------" << "Node Id: " << node->id << "----------" << endl << endl;

    cout << "Successor: " << node->getSuccessor()->id << "     " << "Predecessor: " << node->getPredecessor()->id << endl;
    cout << "FingerTables:" << endl;

    node->fingerTable.print();

    cout << "-------------------------------------" << endl;
    cout << "*************************************" << endl << endl;
}
