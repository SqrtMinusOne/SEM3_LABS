#include <iostream>
#include <vector>

#include "kmp.h"

using namespace std;
int main(int argc, char *argv[])
{
    string T; //Строка
    string P; //Образец
    cin >> P;
    cin >> T;
    vector<int> res = kmp(P, T);
    int n = res.size();
    vector<int>::iterator it;
    if (n > 0){
        for (it = res.begin(); it < --res.end(); it++)
            cout << *it << ",";
        cout << *it;
    }
    else
        cout << "-1";
    cout << endl;
    return 0;
}
