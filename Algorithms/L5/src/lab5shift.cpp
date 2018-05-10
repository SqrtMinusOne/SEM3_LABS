#include <iostream>
#include <vector>

#include "kmp.h"

using namespace std;
int main(int argc, char *argv[])
{
    string A; //Строка 1
    string B; //Строка 2
    cin >> B;
    cin >> A;
    vector<int> res = kmp(A, B, 2);
    int n = res.size();
    if (n > 0){
        cout << res[0];
    }
    else
        cout << "-1";
    cout << endl;
    return 0;
}
