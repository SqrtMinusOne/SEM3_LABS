#ifndef BOHR_H
#define BOHR_H
#include <vector>
#include <string>

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

int SYM(char ch);
void addString(string s, int patternNumber, Node* root);
Node* getSuffLink(Node* v, Node* root);
Node* getLink(Node* v, char c, Node* root);
Node* getUp(Node* v, Node* root);

#endif