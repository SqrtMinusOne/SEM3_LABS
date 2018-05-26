#include "bohr.h"

#define K 27
#define JOK_CONST 32

using namespace std;

Node::Node(){
    son.resize(K);
    son.assign(K, Node_list(0));
    go.resize(K);
    go.assign(K, Node_list(0));
    parent = nullptr;
    suffLink = nullptr;
    up = nullptr;
    isLeaf = false;
    charToParent = 0;
}

Node* isSon(vector<Node_list> & vec, const char_t ch){
    char_t n = SYM(ch);
    for (auto it : vec[n]){
        if (it.ch == ch)
          return it.link;
    }
    return nullptr;
}

Node* addLink(Node* v, vector<Node_list> & vec, const char_t ch){
    char_t n = SYM(ch);
    vec[n].push_back({v, ch}); 
    return v;   
}

Node* addSon(Node* v, vector<Node_list> & vec, const char_t ch){
    //char_t n = SYM(ch);
    Node* node = new Node;
    node->parent = v;
    node->charToParent = ch;
    addLink(node, vec, ch);
    return node;
}

char_t SYM(const char_t ch, const char_t jok){
    static char_t joker = jok;
    if ((joker!=jok) && (jok!=0) && (jok!=JOK_CONST))
        joker = jok;
    if ((ch == 0) && (jok == JOK_CONST))
        return joker;
    else if (((ch == joker) || (jok == JOK_CONST)) && (joker!=0))
        return K - 1;
    return ch % (K - 1);
}

void addString(const string & s, int patternNumber, Node* root, const char_t jok){
    Node* cur = root;
    SYM(0, jok);
    for (size_t i = 0; i < s.length(); i++){
        char_t ch = s[i];
        Node* son = isSon(cur->son, ch);
        if (!son){
            son = addSon(cur, cur->son, ch);
        }
        /* char_t c = SYM(ch, jok);
        if (cur->son[c] == nullptr){
            cur->son[c] = new Node;
            cur->son[c]->parent = cur;
            cur->son[c]->charToParent = ch;
        } */
        cur->isLeaf = false;
        //cur = cur->son[c];
        cur = son;
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

Node* getLink(Node* v, char_t c, Node* root){
  //  char_t nc = SYM(c);
    char_t jok = SYM(0, JOK_CONST);
    Node* goLink = isSon(v->go, c);
    Node* son;
  //  if (v->go[nc] == nullptr){
    if (goLink == nullptr){   
        if ((son = isSon(v->son, c))!=nullptr){
            //v->go[nc] = v->son[nc];
            goLink = addLink(son, v->go, c);
        }
        else if ((son = isSon(v->son, jok))!=nullptr){
            //v->go[jok] = v->son[jok];
            goLink = addLink(son, v->go, jok); 
            //return v->go[jok];
            return goLink;
        }
        else if (v == root)
            goLink = addLink(root, v->go, c);
        else
            goLink = addLink(getLink(getSuffLink(v, root), c, root), v->go, c);
    }
    return goLink;
}

Node* getUp(Node* v, Node* root){
    if (v->up == nullptr){
        if (getSuffLink(v, root)->leafPatternNumber.size())
            v->up = getSuffLink(v, root);
        else if (getSuffLink(v, root) == root)
            v->up = root;
        else
            v->up = getUp(getSuffLink(v, root), root);
    }
    return v->up;
}
