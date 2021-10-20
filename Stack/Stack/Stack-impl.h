/*------------------------------------------------------------------------------
    * File:        Stack-impl.h                                                *
    * Description: Stack functions implementation.                             *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * MIT License                                                              *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#ifndef STACK_STACK_IMPL_H_INCLUDED
#define STACK_STACK_IMPL_H_INCLUDED

#include <utility>
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
    size_(size), capacity_(size)
{
    data_ = new T[size];
    for (size_t i = 0; i < size; i++)
    {
        data_[i] = data[i];
    }
}

template <typename T>
Stack<T>::Stack (const Stack& obj) :
    size_(obj.size_), capacity_(obj.capacity_)
{
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
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
    for (size_t i = 0; i < size_; i++)
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
bool Stack<T>::operator == (const Stack& obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }

    for (size_t i = 0; i < size_; i++)
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
}

template <typename T>
void Stack<T>::push (const T& value)
{
    if (size_ == capacity_)
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
void Stack<T>::swap (Stack* obj)
{
    Stack<T> temp = std::move(*this);
    *this = std::move(*obj);
    *obj = std::move(temp);
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

    for (size_t i = 0; i < size_; i++)
    {
        temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
}

Stack<bool>::Stack () :
    size_(0), capacity_(DEFAULT_CAPACITY)
{
    data_ = new char[capacity_ / 8 + 1];
}

Stack<bool>::Stack (size_t size, bool* data) :
    size_(size), capacity_(size)
{
    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i < size_; i++)
    {
        data_[i / 8] &= ~(1 << (i % 8));
        data_[i / 8] ^= (data[i] << (i % 8));
    }
}

Stack<bool>::~Stack ()
{
    delete[] data_;
}

Stack<bool>::Stack (const Stack& obj) :
    size_(obj.size_), capacity_(obj.capacity_)
{
    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i <= size_ / 8; i++)
    {
        data_[i] = obj.data_[i];
    }
}

Stack<bool>::Stack (Stack&& obj) :
    size_(obj.size_), capacity_(obj.capacity_), data_(obj.data_)
{
    obj.data_ = nullptr;
}

Stack<bool>& Stack<bool>::operator = (const Stack& obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete[] data_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i <= size_ / 8; i++)
    {
        data_[i] = obj.data_[i];
    }

    return *this;
}

Stack<bool>& Stack<bool>::operator = (Stack&& obj)
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

bool Stack<bool>::operator == (const Stack& obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }

    for (size_t i = 0; i < size_; i++)
    {
        if ((data_[i / 8] >> (i % 8)) & 1 != (obj.data_[i / 8] >> (i % 8)) & 1)
        {
            return false;
        }
    }
    return true;
}

bool Stack<bool>::operator != (const Stack& obj) const
{
    return !(*this == obj);
}

void Stack<bool>::push (bool value)
{
    if (size_ == capacity_)
    {
        expand();
    }

    data_[size_ / 8] &= ~(1 << (size_ % 8));
    data_[size_ / 8] ^= (value << (size_ % 8));
    size_++;
}

bool Stack<bool>::top () const
{
    return data_[(size_ - 1) / 8] & (1 << ((size_ - 1) % 8));
}

void Stack<bool>::pop ()
{
    --size_;
}

void Stack<bool>::swap (Stack* obj)
{
    Stack<bool> temp = std::move(*this);
    *this = std::move(*obj);
    *obj = std::move(temp);
}

size_t Stack<bool>::size () const
{
    return size_;
}

bool Stack<bool>::empty () const
{
    return size_ == 0;
}

void Stack<bool>::clear ()
{
    delete[] data_;

    size_ = 0;
    capacity_ = DEFAULT_CAPACITY;
    data_ = new char[capacity_ / 8 + 1];
}

void Stack<bool>::expand ()
{
    capacity_ *= 2;
    char* temp = new char[capacity_ / 8 + 1];

    for (size_t i = 0; i <= size_ / 8; i++)
    {
        temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
}

#endif // STACK_STACK_IMPL_H_INCLUDED

} // namespace puza