#include <iostream>
#include "ahocorasick.h"
#include "bohr.h"

using namespace std;

int main(int argc, char *argv[])
{
    string T;
    int size;
    cin >> T;
    cin >> size;
    vector <string> P(size);
    for (int i = 0; i < size; i++){
        cin >> P[i];
    }
    ACres res = doAhoCorasick(T, P);
    for (auto it : res){
        cout << it.index << " " << it.patternNumber << endl;
    }
}