#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>

class Debug{
public:
    Debug(bool ns = false, unsigned int nl = 0): on(ns), level(nl)
    {}
    void set (bool ns){
        on = ns;
    }
    void setlevel(unsigned int nl){
        level = nl;
    }
    void out(const char* str, int lp = 0){
        if (!on)
            return;
        for (unsigned int i = 0; i <= level + lp; i++){
            std::cout << "#";
        }
        std::cout << " " << str << std::endl;
    }
private:
    bool on = 0;
    unsigned int level = 0;
};
#endif
