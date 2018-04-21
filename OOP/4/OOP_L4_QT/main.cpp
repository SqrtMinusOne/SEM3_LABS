#include <iostream>
#include "list.hpp"

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
    return 0;
}
