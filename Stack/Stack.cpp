/*------------------------------------------------------------------------------
    * File:        Stack.cpp                                                   *
    * Description: Stack functions implementation.                             *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * MIT License                                                              *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Stack.h"

namespace puza {

Stack::Stack () :
    size_(0), capacity_(DEFAULT_CAPACITY)
{
    data_ = new int[capacity_];
}

Stack::Stack (size_t size, int* data) :
    size_(size), capacity_(size  + DEFAULT_CAPACITY), data_(data)
{}

Stack::Stack (const Stack& obj) :
    size_(obj.size_), capacity_(obj.capacity_)
{
    data_ = new int[capacity_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = obj.data_[i];
    }
}

Stack::Stack (Stack&& obj) :
    size_(obj.size_), capacity_(obj.capacity_), data_(obj.data_)
{
    obj.data_ = nullptr;
}

Stack& Stack::operator = (const Stack& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete[] data_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    data_ = new int[capacity_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = obj.data_[i];
    }

    return *this;
}

Stack& Stack::operator = (Stack&& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    delete[] data_;
    data_ = obj.data_;
    obj.data_ = nullptr;
 
    return *this;
}

bool Stack::operator == (const Stack& obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }

    for (size_t i = 0; i < size_; ++i)
    {
        if (data_[i] != obj.data_[i])
        {
            return false;
        }
    }
    return true;
}

bool Stack::operator != (const Stack& obj) const
{
    return !(*this == obj);
}

Stack::~Stack ()
{
    delete[] data_;
    data_ = nullptr;
}

void Stack::push (int value)
{
    if (size_ == capacity_ - 1)
    {
        expand();
    }

    data_[size_++] = value;
}

void Stack::pop ()
{
    --size_;
}

int& Stack::top ()
{
    return data_[size_ - 1];
}

const int& Stack::top () const
{
    return data_[size_ - 1];
}

size_t Stack::size () const
{
    return size_;
}

bool Stack::empty () const
{
    return size_ == 0;
}

void Stack::clean ()
{
    delete[] data_;

    size_ = 0;
    capacity_ = DEFAULT_CAPACITY;

    data_ = new int[capacity_];
}

void Stack::expand ()
{
    capacity_ *= 2;

    int* temp = new int[capacity_];

    for (size_t i = 0; i < size_; ++i)
        temp[i] = data_[i];

    delete[] data_;
    data_ = temp;
}

} // namespace puza