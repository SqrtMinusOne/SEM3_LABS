#include <iostream>
#include <vector>
#include <ahocorasick.h>
#include <bohr.h>

using namespace std;

int main(int argc, char *argv[])
{
    string T;
    string P;
    char Joker;
    cin >> T;
    cin >> P;
    cin >> Joker;
    ACres res = doAhoCorasick(T, vector<string> {P}, Joker);
    for (auto it : res){
        cout << it.index << endl;
    }
}
