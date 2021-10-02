/*------------------------------------------------------------------------------
    * File:        Stack.cpp                                                   *
    * Description: Stack functions implementation.                             *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Stack.h"
#include <new>

constexpr size_t DEFAULT_STACK_CAPACITY = 8;

Stack::Stack () :
    size_(0),
    capacity_(DEFAULT_STACK_CAPACITY)
{
    data_ = new int[capacity_] {};
}

Stack::Stack (const Stack& obj) :
    size_    (obj.size_),
    capacity_(obj.capacity_)
{
    data_ = new int[capacity_] {};

    for (size_t i = 0; i < capacity_; ++i)
        data_[i] = obj.data_[i];
}

Stack::Stack (Stack&& obj) :
    size_    (obj.size_),
    capacity_(obj.capacity_),
    data_    (obj.data_)
{
    obj.data_ = nullptr;
}

Stack& Stack::operator = (const Stack& obj)
{
    delete[] data_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    data_ = new int[capacity_]{};

    for (size_t i = 0; i < capacity_; ++i)
        data_[i] = obj.data_[i];

    return *this;
}

Stack& Stack::operator = (Stack&& obj)
{
    size_ = obj.size_;
    capacity_ = obj.capacity_;

    delete[] data_;
    data_ = obj.data_;
    obj.data_ = nullptr;
 
    return *this;
}

Stack::~Stack ()
{
    if (data_ != nullptr)
        delete[] data_;

    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

void Stack::push (int value)
{
    if (size_ == capacity_ - 1)
        expand();

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

int Stack::top () const
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
    capacity_ = DEFAULT_STACK_CAPACITY;

    data_ = new int[capacity_] {};
}

void Stack::expand ()
{
    capacity_ *= 2;

    int* temp = new int[capacity_] {};

    for (size_t i = 0; i < capacity_ / 2; ++i)
        temp[i] = data_[i];

    delete[] data_;
    data_ = temp;
}