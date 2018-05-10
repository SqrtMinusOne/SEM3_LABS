#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "kmp.h"

using namespace std;

unsigned short int wordsLengthDispersion(unsigned short int num){
    vector<unsigned short int> English {0, 10, 39, 53, 67, 79, 84, 89, 93, 96, 98, 99, 100};
    unsigned short int i;
    for (i = 0; i < English.size(); i++){
        if (num < English[i])
            return i;
    }
    return i;
}

string randomWord(unsigned short int len){
    string res;
    res.resize(len);
    for (unsigned short int i = 0; i < len; i++){
        char t = rand() % 26 + 'a';
        res[i] = t;
    }
    return res;
}

string randomString(unsigned int n, bool spaces = true){
    string res;
    for (unsigned int i = 0; i < n; i++){
        res.append(randomWord(wordsLengthDispersion(rand()%100)));
        if (spaces)
            res.append(" ");
    }
    return res;
}

void ProgTest(){
    unsigned int Tstart; unsigned int Tend; unsigned int Tstep;
    unsigned int Pstart; unsigned int Pend; unsigned int Pstep;
    bool spaces;
    cout << "Enter text parameters: start words number, end words number, step" << endl;
    cin >> Tstart >> Tend >> Tstep;
    cout << "Enter sample parameters: start lenght, end lenght, step" << endl;
    cin >> Pstart >> Pend >> Pstep;
    cout << "Text with/without spaces [1/0]? ";
    cin >> spaces;
    ofstream out;
    out.open("results.csv");
    out << "Text lenght,Sample lenght,KMP operations,Naive operations, Found" << endl;
    cout << "Text lenght,Sample lenght,KMP operations,Naive operations, Found" << endl;
    unsigned int Tl; unsigned int Pl;
    for (Tl = Tstart; Tl <= Tend; Tl = Tl + Tstep){
        for (Pl = Pstart; Pl <= Pend; Pl = Pl + Pstep){
            string T = randomString(Tl, spaces);
            string P = randomWord(Pl);
            int countKMP = 0;
            int countNaive = 0;
            vector<int> res = kmp(P, T, 1, &countKMP);
            naive(P, T, &countNaive);
            out << Tl << "," << Pl << "," << countKMP << "," << countNaive << "," << res.size() << endl;
            cout << Tl << "," << Pl << "," << countKMP << "," << countNaive << "," << res.size() << endl;
        }
    }
    out.close();
}

void CustomTest()
{
    string T; //Строка
    string P; //Образец
    cin >> P;
    cin >> T;
    int count1 = 0;
    int count2 = 0;
    vector<int> res = kmp(P, T, 1, &count1);
    vector<int> res2 = naive(P, T, &count2);
    cout << count1 << " " << count2 << endl;
    int n = res.size();
    vector<int>::iterator it;
    if (n > 0)
    {
        for (it = res.begin(); it < --res.end(); it++)
            cout << *it << ",";
        cout << *it << endl;
        for (it = res2.begin(); it < --res2.end(); it++)
            cout << *it << ",";
        cout << *it << endl;
    }
    else
        cout << "-1";
    cout << endl;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    cout << "1 - User Test" << endl
         << "2 - Programmed test" << endl;
    short int m;
    cin >> m;
    if (m == 1)
    {
        CustomTest();
    }
    else
    {
        ProgTest();
    }
    return 0;
}
