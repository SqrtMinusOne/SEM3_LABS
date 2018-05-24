#ifndef BOHR_H
#define BOHR_H
#include <vector>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

typedef struct Node{
    vector<Node*> son; //Children
    vector<Node*> go; //Transitions
    Node* parent;
    char charToParent;
    Node* suffLink;
    Node* up; //Compressed suffix link
    bool isLeaf;
    vector<int> leafPatternNumber;
    Node();
}Node;

char SYM(const char ch, const char jok = 0);

void addString(const string & s, int patternNumber, Node* root, const char jok = 0);
void out(Node* n);
Node* getSuffLink(Node* v, Node* root);
Node* getLink(Node* v, char c, Node* root);
Node* getUp(Node* v, Node* root);

#endif
