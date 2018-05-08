#include "kmp.h"

using namespace std;
vector<int> kmp(const string & P, const string & T, unsigned int multiplier){
    vector<int> answer;
    int j=0;
    vector<int> p = prefix(P);
    unsigned int Tsize = T.size();
    for (size_t i=0; i<(Tsize * multiplier); i++){
        while ((j > 0) && (T[i%Tsize] != P[j]))
            j = p[j-1];
        if (T[i%Tsize] == P[j])
            j++;
        if (j==P.size())
            answer.push_back(i-j+1);
    }
    return answer;
}
