#ifndef ALG_H
#define ALG_H

#include <vector>
#include "bohr.h"

typedef struct ACresEl{
    size_t index;
    int patternNumber;
    ACresEl(size_t ind, int pN);
}ACresEl;

typedef vector<ACresEl> ACres;

void processText(string & T, Node* root, ACres & res);

#endif