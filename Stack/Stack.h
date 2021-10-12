/*------------------------------------------------------------------------------
    * File:        Stack.h                                                     *
    * Description: Stack library.                                              *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * MIT License                                                              *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#ifndef STACK_STACK_H_INCLUDED
#define STACK_STACK_H_INCLUDED

#include <cstdlib>

namespace puza {

template <typename T>
class Stack
{
public:

    Stack ();
    Stack (size_t size, T* data);
    ~Stack ();


    Stack (const Stack& obj);
    Stack (Stack&& obj);

    Stack& operator = (const Stack& obj);
    Stack& operator = (Stack&& obj);

    bool operator == (const Stack& obj) const;
    bool operator != (const Stack& obj) const;

    void push (T value);
    void pop  ();

    const T& top () const;
    T& top ();

    bool   empty () const;
    size_t size  () const;
    void   clear ();

private:

    size_t size_;
    size_t capacity_;
    T*   data_;

    static const size_t DEFAULT_CAPACITY = 8;

    void expand ();
};

} // namespace puza

#endif // STACK_STACK_H_INCLUDED
