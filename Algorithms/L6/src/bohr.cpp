#include "bohr.h"

#define K 26

using namespace std;

Node::Node(){
    son.resize(K);
    son.assign(K, nullptr);
    go.resize(K);
    go.assign(K, nullptr);
    parent = nullptr;
    suffLink = nullptr;
    up = nullptr;
    isLeaf = false;
    charToParent = 0;
}

char SYM(const char ch){
    return tolower(ch) - 'a';

}

void out(Node* n){
    stack<Node*> q;
    q.push(n);
    while (!q.empty()){
        Node* cur = q.top();
        q.pop();
        if (cur->charToParent!=0)
            cout << cur->charToParent;
        if (!cur->leafPatternNumber.empty())
            cout << "!";
        cout << " ";
        if (cur->isLeaf){
            cout << endl;
        }
        else for (int i = K-1; i >= 0; i--){
            if (cur->son[i]!=nullptr)
                q.push(cur->son[i]);
        }
    }
}

void addString(string s, int patternNumber, Node* root){
    Node* cur = root;
    for (size_t i = 0; i < s.length(); i++){
        char ch = s[i];
        char c = SYM(ch);
        if (cur->son[c] == nullptr){
            cur->son[c] = new Node;
            cur->son[c]->parent = cur;
            cur->son[c]->charToParent = ch;
        }
        cur->isLeaf = false;
        cur = cur->son[c];
    }
    cur->isLeaf = true;
    cur->leafPatternNumber.push_back(patternNumber);
}

Node* getSuffLink(Node* v, Node* root){
    if (v->suffLink == nullptr){
        if ((v == root) || (v->parent == root))
            v->suffLink = root;
        else
            v->suffLink = getLink(getSuffLink(v->parent, root), v->charToParent, root);
    }
    return v->suffLink;
}

Node* getLink(Node* v, char c, Node* root){
    char nc = SYM(c);
    if (v->go[nc] == nullptr){
        if (v->son[nc])
            v->go[nc] = v->son[nc];
        else if (v == root)
            v->go[nc] = root;
        else
            v->go[nc] = getLink(getSuffLink(v, root), c, root);
    }
    return v->go[nc];
}

Node* getUp(Node* v, Node* root){
    if (v->up == nullptr){
        if (getSuffLink(v, root)->isLeaf)
            v->up = getSuffLink(v, root);
        else if (getSuffLink(v, root) == root)
            v->up = root;
        else
            v->up = getUp(getSuffLink(v, root), root);
    }
    return v->up;
}