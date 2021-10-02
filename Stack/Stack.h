/*------------------------------------------------------------------------------
    * File:        Stack.h                                                     *
    * Description: Stack library.                                              *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#ifndef STACK_STACK_H_INCLUDED
#define STACK_STACK_H_INCLUDED

#include <cstdlib>

class Stack
{
    size_t size_;
    size_t capacity_;

    int* data_;

public:

    Stack ();

    Stack (const Stack& obj);
    Stack (Stack&& obj);

    Stack& operator = (const Stack& obj);
    Stack& operator = (Stack&& obj);

    ~Stack ();

    void   push  (int value);
    void   pop   ();
    int&   top   ();
    int    top   () const;
    bool   empty () const;
    size_t size  () const;
    void   clean ();

private:

    void expand ();
};

#endif // STACK_STACK_H_INCLUDED
