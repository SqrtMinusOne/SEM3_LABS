#include <iostream>
#include "shared_ptr.hpp"
#include "debug.hpp"

using namespace std;
using stepik::shared_ptr;

#define DEBUG

class MyClass{
public:
    MyClass(int b = 0): a(b)
    { }
    int get() {return a;}
    void set(int b = 0) {a = b;}
    void print(){
        cout << a << endl;
    }
private:
    int a;
};

int main()
{
    Debug debug(true, 0);
    debug.out("Constructor test");
    MyClass* obj = new MyClass(15);
    shared_ptr<MyClass> ap(obj);
    debug.out("Get test");
    ap.get()->print();
    debug.out("Operator * test");
    (*ap).print();
    debug.out("Operator -> test");
    ap->print();
    debug.out("Copy constructor test");
    shared_ptr<MyClass> bp(ap);
    shared_ptr<MyClass> cp(bp);
    cout << ap.use_count() << " " << bp.use_count() << " " << cp.use_count() << endl;
    debug.out("End of program");
    return 0;
}
