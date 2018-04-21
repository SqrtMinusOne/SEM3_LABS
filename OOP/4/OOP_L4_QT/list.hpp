#ifndef LIST_HPP
#define LIST_HPP
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

#define DEBUG

namespace stepik
{
template <class Type>
struct node
{
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
        : value(value), next(next), prev(prev)
    {
    }
};

template <class Type>
class list
{
public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    void Debug(const char* str){
#ifdef DEBUG
        std::cout << "#: " << str << std::endl;
#endif //DEBUG
    }

    list()
        : m_head(nullptr), m_tail(nullptr)
    {
        Debug("Initializing empty list");
    }

    //================|Stepik 2_2_2|================
    ~list()
    {
        Debug("Destructor");
        clear();
    }

    void swap(list& first, list& second)
    {
        Debug("Swap");
        using std::swap;
        swap(first.m_head, second.m_head);
        swap(first.m_tail, second.m_tail);
    }

    list(const list& other) : list()
    {
        Debug("Copy constructor");
        for (node<Type>* otherref = other.m_head; otherref; otherref = otherref->next){
            push_back(otherref->value);
        }
    }

    list(list&& other) : list()
    {
        Debug("Move constructor");
        swap(*this, other);
    }

    list& operator= (const list& other)
    {
        Debug("Assignment copy operator");
        if (!empty())
            clear();
        for (node<Type>* otherref = other.m_head; otherref; otherref = otherref->next){
            push_back(otherref->value);
        }
        return *this;
    }


    //================|Stepik 2_2_1|================


    void push_back(const value_type& value)
    {
        Debug("Push back");
        if (!empty()){
            m_tail->next = new node<Type>(value, nullptr, m_tail);
            m_tail = m_tail->next;
        }
        else{
            m_tail = new node<Type>(value, nullptr, nullptr);
            m_head = m_tail;
        }
    }

    void push_front(const value_type& value)
    {
        Debug("Push front");
        if (!empty()){
            m_head->prev = new node<Type> (value, m_head, nullptr);
            m_head = m_head->prev;
        }
        else{
            m_head = new node<Type>(value, nullptr, nullptr);
            m_tail = m_head;
        }
    }

    reference front()
    {
        return m_head->value;
    }

    const_reference front() const
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }

    const_reference back() const
    {
        return m_tail->value;
    }

    void pop_front()
    {
        Debug("Pop front");
        if (m_head){
            if (m_head->next){
                m_head = m_head->next;
                delete m_head->prev;
                m_head->prev = nullptr;
            }
            else{
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
            }
        }
    }

    void pop_back()
    {
        Debug("Pop back");
        if (m_tail){
            if (m_tail->prev){
                m_tail = m_tail->prev;
                delete m_tail->next;
                m_tail->next = nullptr;
            }
            else{
                delete m_tail;
                m_tail = nullptr;
                m_head = nullptr;
            }
        }
    }

    void clear()
    {
        Debug("Clear");
        while (!empty())
            pop_back();
    }

    bool empty() const
    {
        return (!m_head && !m_tail);
    }

    size_t size() const
    {
        node<Type>* ref = m_head;
        size_t res;
        for (res = 0; ref; res
             ++, ref = ref->next);
        return res;
    }

    void out(){
        std::cout << "OUT: " << size() << ": ";
        for (node<Type>* ref = m_head; ref; ref = ref->next){
            std::cout << ref->value << " ";
        }
        std::cout << std::endl;
    }

private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

}// namespace stepik
#endif // LIST_HPP
