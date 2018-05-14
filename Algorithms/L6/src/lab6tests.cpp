#include "bohr.h"
//#include "gtest/gtesh.h"
#include <iostream>

void out(Node* n){
    if (n == nullptr)
        return;
    cout << n->charToParent;
    if (n->leafPatternNumber.size()!=0)
        cout << "!";
    cout << " ";
    for (int i = 0; i < 26; i++){
        out(n->son[i]);
    }
    if (n->isLeaf)
        cout << endl;
}

int main()
{
    for (char i = 'a'; i <= 'z'; i++)
        cout << SYM(i) << " ";
    cout << endl;
    Node* root = new Node;
    addString("his", 0, root);
    addString("he", 1, root);
    addString("hers", 2, root);
    addString("she", 3, root);
    out(root);
    return 0;
}