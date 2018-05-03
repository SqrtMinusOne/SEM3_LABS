#include "kmp.h"

using namespace std;
vector<int> kmp(string P, string T){
    int pl = P.length();
    int tl = T.length();
    vector<int> answer;
    vector<int> p = prefix(P + "#" + T);
    for (int i=0; i<tl; i++){
        if (p[pl+i+1] == pl)
            answer.push_back(i - pl + 1);
    }
    return answer;
}
