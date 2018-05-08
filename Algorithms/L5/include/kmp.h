#ifndef KMP_H
#define KMP_H
#include <vector>
#include <iostream>
#include "prefix.h"
using namespace std;

vector<int> kmp(const string & P, const string & T, unsigned int multiplier = 1);

#endif
