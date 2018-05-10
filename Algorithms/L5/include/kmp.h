#ifndef KMP_H
#define KMP_H
#include <vector>
#include <iostream>
#include "prefix.h"
using namespace std;

inline void INC(int* x);

vector<int> kmp(const string & P, const string & T, unsigned int multiplier = 1, int* counter = nullptr);
vector<int> naive(const string & P, const string & T, int* counter = nullptr);

#endif
