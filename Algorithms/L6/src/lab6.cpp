#include <iostream>
#include "ahocorasick.h"
#include "bohr.h"

using namespace std;

int main()
{
    string T;
    string P;
    int size;
    ACres res;
    Node* bohr = new Node;
    cin >> T;
    cin >> size;
    res.resize(size);
    for (int i = 0; i < size; i++){
        cin >> P;
        addString(P, i, bohr);
    }
    processText(T, bohr, res);
    for (int i = 0; i < size; i++){
        for (int k = 0; k < res[i].size(); k++){
            cout << res[i][k] << " ";
        }
        cout << endl;
    }
}