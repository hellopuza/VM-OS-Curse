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

template <typename T>
Stack<T>::Stack () :
    size_(0), capacity_(DEFAULT_CAPACITY)
{
    data_ = new T[capacity_];
}

template <typename T>
Stack<T>::Stack (size_t size, T* data) :
    size_(size), capacity_(size  + DEFAULT_CAPACITY), data_(data)
{}

template <typename T>
Stack<T>::Stack (const Stack& obj) :
    size_(obj.size_), capacity_(obj.capacity_)
{
    data_ = new T[capacity_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = obj.data_[i];
    }
}

template <typename T>
Stack<T>::Stack (Stack&& obj) :
    size_(obj.size_), capacity_(obj.capacity_), data_(obj.data_)
{
    obj.data_ = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete[] data_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    data_ = new T[capacity_];

    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = obj.data_[i];
    }

    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator = (Stack&& obj)
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

template <typename T>
bool Stack<T>::operator == (const Stack<T>& obj) const
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

template <typename T>
bool Stack<T>::operator != (const Stack& obj) const
{
    return !(*this == obj);
}

template <typename T>
Stack<T>::~Stack ()
{
    delete[] data_;
    data_ = nullptr;
}

template <typename T>
void Stack<T>::push (T value)
{
    if (size_ == capacity_ - 1)
    {
        expand();
    }

    data_[size_++] = value;
}

template <typename T>
void Stack<T>::pop ()
{
    --size_;
}

template <typename T>
T& Stack<T>::top ()
{
    return data_[size_ - 1];
}

template <typename T>
const T& Stack<T>::top () const
{
    return data_[size_ - 1];
}

template <typename T>
size_t Stack<T>::size () const
{
    return size_;
}

template <typename T>
bool Stack<T>::empty () const
{
    return size_ == 0;
}

template <typename T>
void Stack<T>::clear ()
{
    delete[] data_;

    size_ = 0;
    capacity_ = DEFAULT_CAPACITY;

    data_ = new T[capacity_];
}

template <typename T>
void Stack<T>::expand ()
{
    capacity_ *= 2;

    T* temp = new T[capacity_];

    for (size_t i = 0; i < size_; ++i)
        temp[i] = data_[i];

    delete[] data_;
    data_ = temp;
}

} // namespace puza