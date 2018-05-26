#ifndef BOHR_H
#define BOHR_H
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <iostream>

using namespace std;

typedef short unsigned int char_t;

struct Node;

typedef struct Node_link{
    Node* link;
    char_t ch;
}Node_link;

typedef list<Node_link> Node_list;

typedef struct Node{
    vector<Node_list> son; //Children
    vector<Node_list> go; //Transitions
    Node* parent;
    char_t charToParent;
    Node* suffLink;
    Node* up; //Compressed suffix link
    bool isLeaf;
    vector<int> leafPatternNumber; //test
    Node();
}Node;

char_t SYM(const char_t ch, const char_t jok = 0);
Node* isSon(vector<Node_list> & vec, const char_t ch);
Node* addSon(Node* v, vector<Node_list> & vec, const char_t ch);

void addString(const string & s, int patternNumber, Node* root, const char_t jok = 0);
void out(Node* n);
Node* getSuffLink(Node* v, Node* root);
Node* getLink(Node* v, char_t c, Node* root);
Node* getUp(Node* v, Node* root);

#endif
