#include "debug.hpp"

namespace stepik
{
template <typename T>
class shared_ptr
{
public:
    typedef long unsigned int count_type;
    explicit shared_ptr(T *ptr = 0)
    {
        debug = new Debug(true, 1);
        debug->out("Constructor");
        if (ptr == 0){
            debug->out("No object", 1);
            object = nullptr;
            count_ptr = new count_type(0);
        }
        else{
            debug->out("Object exists", 1);
            object = ptr;
            count_ptr = new count_type(1);
        }
    }

    ~shared_ptr()
    {
        debug->out("Destructor");
        if (object!=0){
            debug->out("Count--", 1);
            (*(count_ptr))--;
        }
        if (use_count() == 0){
            debug->out("Delete", 2);
            delete object;
        }
    }

    shared_ptr(const shared_ptr & other): object(other.object), count_ptr(other.count_ptr)
    {
        debug->out("Copy constructor");
        if (get()!=0)
            (*(count_ptr))++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        // implement this
    }

    explicit operator bool() const
    {
        return (get()!= 0);
    }

    T* get() const
    {
        debug->out("Get operator");
        return object;
    }

    long use_count() const
    {
        return *count_ptr;
    }

    T& operator*() const
    {
        return *object;
    }

    T* operator->() const
    {
        return object;
    }

    void swap(shared_ptr& x) noexcept
    {
        debug->out("Swap");
        std::swap(x.object, object);
        std::swap(x.count_ptr, count_ptr);
    }

    void reset(T *ptr = 0)
    {
        // implement this
    }

private:
    T* object;
    count_type* count_ptr;
    Debug* debug;
};
} // namespace stepik
