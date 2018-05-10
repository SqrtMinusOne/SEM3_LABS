#include "prefix.h"

using namespace std;

void INC(int* x){
    if (x!=nullptr)
        (*(x))++;
}

bool CMP(const char& a, const char& b, int* counter){
    INC(counter);
 //  cout << a << " = " << b << endl;
    return a == b;
}

vector<int> prefix (const string & S, int* counter) {
    int n = S.length();
    vector<int> p(n);
    for (int i=1; i<n; i++) {
        bool temp = false;
        int j = p[i-1];
        while ((j > 0) && (!(temp = CMP(S[i], S[j], counter)))){
            j = p[j-1];
        }
        if ((temp) || (CMP(S[i],S[j], counter))){
            j++;
        }
        p[i] = j;
    }
    return p;
}