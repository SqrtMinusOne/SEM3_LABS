#ifndef ALG_H
#define ALG_H

#include <vector>
#include "bohr.h"

using namespace std;

typedef struct ACresEl{
    size_t index;
    int patternNumber;
    ACresEl(size_t ind, int pN);
}ACresEl;

typedef vector<ACresEl> ACres;

bool CMP (const ACres & a, const ACres & b);
void convertStepik(ACres & res, vector<size_t> & len);

void processText(const string & T, Node* root, ACres & res);

ACres doAhoCorasick(const string & T, const vector<string> & P, const char joker = 0);

#endif
