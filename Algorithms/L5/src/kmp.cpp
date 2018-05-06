#include "kmp.h"

using namespace std;
vector<int> kmp(string P, string T){
    vector<int> answer;
    int j=0;
    vector<int> p = prefix(P);
    for (size_t i=0; i<T.size(); i++){
        while ((j > 0) && (T[i] != P[j]))
            j = p[j-1];
        if (T[i] == P[j])
            j++;
        if (j==P.size())
            answer.push_back(i-j+1);
    }
    return answer;
}
