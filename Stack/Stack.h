/*------------------------------------------------------------------------------
    * File:        Stack.h                                                     *
    * Description: Stack library.                                              *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <new>

const size_t DEFAULT_STACK_CAPACITY = 8;

template <typename TYPE>
class Stack
{
private:

    size_t  capacity_ = DEFAULT_STACK_CAPACITY;
    size_t  size_cur_ = 0;

    TYPE* data_ = nullptr;

public:

    Stack ()
    {
        data_ = new TYPE[capacity_] {};
    }

    Stack (const Stack& obj) :
        size_cur_(obj.size_cur_),
        capacity_(obj.capacity_)
    {
        data_ = new TYPE[capacity_] {};

        for (size_t i = 0; i < capacity_; ++i)
            data_[i] = obj.data_[i];
    }

    Stack& operator = (const Stack& obj)
    {
        delete[] data_;

        size_cur_ = obj.size_cur_;
        capacity_ = obj.capacity_;

        data_ = new TYPE[capacity_]{};

        for (size_t i = 0; i < capacity_; ++i)
            data_[i] = obj.data_[i];
    }

    ~Stack ()
    {
        size_cur_ = 0;

        if (data_ != nullptr) delete[] data_;
        data_ = nullptr;

        capacity_ = 0;
    }

    void push (TYPE value)
    {
        if (size_cur_ == capacity_ - 1) Expand();

        data_[size_cur_++] = value;
    }

    TYPE pop ()
    {
        if (size_cur_ == 0)
        {
            delete[] data_;
            printf("Stack is empty\n");
            exit(-1);
        }
        
        return data_[--size_cur_];
    }

    TYPE top ()
    {
        if (size_cur_ == 0)
        {
            delete[] data_;
            printf("Stack is empty\n");
            exit(-1);
        }

        return data_[size_cur_ - 1];
    }

    size_t getSize () const
    {
        return size_cur_;
    }

    void clean ()
    {
        size_cur_ = 0;
        delete[] data_;

        capacity_ = DEFAULT_STACK_CAPACITY;

        data_ = new TYPE[capacity_] {};
    }

private:

    void Expand ()
    {
        capacity_ *= 2;

        TYPE* temp = new TYPE[capacity_] {};

        for (size_t i = 0; i < capacity_ / 2; ++i)
            temp[i] = data_[i];

        delete[] data_;
        data_ = temp;
    }
};

#endif // STACK_H_INCLUDED
