#ifndef PREFIX_H
#define PREFIX_H

#include <vector>
#include <iostream>
using namespace std;

void INC(int* x);
bool CMP(const char& a, const char& b, int* counter);
vector<int> prefix (const string & S, int* counter = nullptr);

#endif
