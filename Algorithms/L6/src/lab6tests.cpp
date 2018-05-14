#include "bohr.h"
//#include "gtest/gtesh.h"
#include <iostream>



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
    Node* e = root->son[SYM('s')]->son[SYM('h')]->son[SYM('e')];
    getSuffLink(e, root);
    out(root);
    return 0;
}