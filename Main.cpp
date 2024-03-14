#include "Node.h"
#include <math.h>
#include <map>
#include "Helpers.h"
#include <iostream>

map<int, Node*> nodeMap;
vector<int> keysVector;

// This is the main function that will be called from the command line

int main(){
    cout << "!! CHORD DHT Implementation !!" << endl;
    cout << "- By Sanjana Patil" << endl;

    Node n0 = Node(0);
    Node n1 = Node(30);
    Node n2 = Node(65);
    Node n3 = Node(110);
    Node n4 = Node(160);
    Node n5 = Node(230);

    n0.join(NULL);
    n1.join(&n0);
    n2.join(&n1);
    n3.join(&n2);
    n4.join(&n3);
    n5.join(&n4);

    printAllFingerTables();

    n0.insert(3, 3);
    n1.insert(200);
    n2.insert(123);
    n3.insert(45,3);
    n4.insert(99);
    n2.insert(60,10);
    n0.insert(50,8);
    n3.insert(100,5);
    n3.insert(101,4);
    n3.insert(102,6);
    n5.insert(240,8);
    n5.insert(250,10);

    printLocalTableForAllNodes();

    Node n6 = Node(100);
    n6.join(&n2);

    printLookupResultsForAllKeysOnNode(&n0);
    printLookupResultsForAllKeysOnNode(&n2);
    printLookupResultsForAllKeysOnNode(&n6);

    return 0;
}
