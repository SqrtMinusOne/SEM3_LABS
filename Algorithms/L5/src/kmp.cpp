#include "kmp.h"
#include "prefix.h"

using namespace std;

vector<int> kmp(const string & P, const string & T, unsigned int multiplier, int* counter){
    vector<int> answer;
    int j=0;
    vector<int> p = prefix(P, counter);
    unsigned int Tsize = T.size();
    for (size_t i=0; i<(Tsize * multiplier); i++){
        bool temp = false;
        while ((j > 0) && (!(temp = CMP(T[i%Tsize], P[j], counter)))){
            j = p[j-1];
        }
        if ((temp) || (CMP(T[i%Tsize], P[j], counter))){
            j++;
        }
        if (j==P.size())
            answer.push_back(i-j+1);
    }
    return answer;
}


vector<int> naive(const string & P, const string & T, int* counter){
    vector<int> answer;
    int j=0;
    int k=0;
    unsigned int Tsize = T.size();
    unsigned int Psize = P.size();
    for (size_t i=0; i<=(Tsize - Psize); i++){
        k=0;
        while (CMP(T[i+k], P[j+k], counter) && (k < Psize)){
            k++;
        }
        if (k == Psize)
            answer.push_back(i);
    }
    return answer;
}