#include "prefix.h"

using namespace std;
vector<int> prefix (const string & S) {
    int n = S.length();
    vector<int> p(n);
    for (int i=1; i<n; i++) {
        int j = p[i-1];
        while ((j > 0) && (S[i] != S[j]))
            j = p[j-1];
        if (S[i] == S[j])
            j++;
        p[i] = j;
    }
    return p;
}
