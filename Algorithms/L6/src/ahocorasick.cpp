#include "ahocorasick.h"
#include "bohr.h"

ACresEl::ACresEl(size_t ind, int pN): index(ind), patternNumber(pN)
{}

void processText(string & T, Node* root, ACres & res){
    Node* cur = root;
    for (size_t i = 0; i < T.length(); i++){
        char c = T[i];
        cur = getLink(cur, c, root);
        for (Node* u = cur; u != root; u = getUp(u, root)){
            if (u->leafPatternNumber.size()!=0)
                for (auto it : u->leafPatternNumber){
                    res.push_back(ACresEl(i, it));
                }
        }
    }
}