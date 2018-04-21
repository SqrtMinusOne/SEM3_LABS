#include <iostream>
#include "list.hpp"
#include <list>
using namespace std;

int main()
{
    cout << "===|Initializing test|===" << endl;
    stepik::list<int> ls;
    cout << "Size: " << ls.size() << endl;
    cout << "===|Push test|===" << endl;
    ls.push_front(10);
    ls.push_front(20);
    cout << "Size: " << ls.size() << endl;
    ls.push_back(-10);
    ls.push_back(-20);
    cout << "Size: " << ls.size() << endl;
    ls.out();
    cout << "===|References test|===" << endl;
    cout << ls.back() << " " << ls.front() << endl;
    cout << "===|Clear test|===" << endl;
    ls.clear();
    ls.out();
    cout << "===|Copy constructor test|===" << endl;
    stepik::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    stepik::list<int> lst2(lst);
    lst2.out();
    lst.out();
    lst.clear();
    lst2.out();
    lst.out();
    cout << "===|Move constructor test|===" << endl;
    stepik::list<int> ls2 (std::move(lst2));
    lst2.out();
    ls2.out();
    cout << "===|Assingment constructor test|===" << endl;
    ls = ls2;
    ls.out();
    ls2.out();
    cout << "===|End|===" << endl;
    return 0;
}
