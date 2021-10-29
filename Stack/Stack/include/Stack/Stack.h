#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <cstdlib>

namespace puza {

template<typename T>
class Stack
{
public:
    Stack ();
    Stack (size_t size, const T *data);
    Stack (const Stack &obj);
    Stack (Stack &&obj) noexcept;
    ~Stack ();

    Stack &operator= (const Stack &obj);
    Stack &operator= (Stack &&obj) noexcept;
    bool operator== (const Stack &obj) const;
    bool operator!= (const Stack &obj) const;

    void push (const T &value);
    void pop ();
    const T &top () const;
    T &top ();

    void swap (Stack *obj);
    bool empty () const;
    size_t size () const;
    void clear ();

    const size_t DEFAULT_CAPACITY = 16;

private:
    size_t size_;
    size_t capacity_;
    T *data_;

    void expand ();
};

template<>
class Stack<bool>
{
public:
    Stack ();
    Stack (size_t size, const bool *data);
    Stack (const Stack &obj);
    Stack (Stack &&obj) noexcept;
    ~Stack ();

    Stack &operator= (const Stack &obj);
    Stack &operator= (Stack &&obj) noexcept;
    bool operator== (const Stack &obj) const;
    bool operator!= (const Stack &obj) const;

    void push (bool value);
    void pop ();
    bool top () const;

    void swap (Stack *obj);
    bool empty () const;
    size_t size () const;
    void clear ();

    const size_t DEFAULT_CAPACITY = 16;

private:
    size_t size_;
    size_t capacity_;
    char *data_;

    void expand ();
};

} // namespace puza

#endif // STACK_STACK_H