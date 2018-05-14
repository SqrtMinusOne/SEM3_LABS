#include <iostream>
#include "ahocorasick.h"
#include "bohr.h"

using namespace std;

int main(int argc, char *argv[])
{
    string T;
    string P;
    int size;
    ACres res;
    Node* bohr = new Node;
    cin >> T;
    cin >> size;
    vector <size_t> len(size);
    for (int i = 0; i < size; i++){
        cin >> P;
        addString(P, i, bohr);
        len[i] = P.length();
    }
    processText(T, bohr, res);
    for (auto it : res){
        cout << it.index + 2 - len[it.patternNumber] << " " << it.patternNumber + 1 << endl;
    }
}