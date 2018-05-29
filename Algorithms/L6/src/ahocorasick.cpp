#include "ahocorasick.h"
#include "bohr.h"

ACresEl::ACresEl(size_t ind, int pN): index(ind), patternNumber(pN)
{}

bool CMP (const ACres & a, const ACres & b){
    if (a.size()!=b.size())
        return 0;
    ACres::const_iterator ait;
    ACres::const_iterator bit = b.begin();
    for (ait = a.begin(); (ait < a.end()) && (bit < b.end()); ait++, bit++){
        if ((ait->index!=bit->index) || (ait->patternNumber!=bit->patternNumber))
            return 0;
    }
    return 1;
}

void processText(const string & T, Node* root, ACres & res){
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

void convertStepik(ACres & res, vector<size_t> & len){
    ACres::iterator it;
    for (it = res.begin(); it < res.end(); it++){
        it->index = it->index + 2 - len[it->patternNumber];
        it->patternNumber++;
    }
}

ACres doAhoCorasick(const string & T, const vector<string> & P,  const char joker){
    ACres res;
    Node* bohr = new Node;
    size_t size = P.size();
    vector <size_t> len(size);
    int i = 0;
    for (auto it : P){
        addString(it, i, bohr, joker);
        len[i++] = it.length();
    }
    processText(T, bohr, res);
    convertStepik(res, len);

    return res;
}
