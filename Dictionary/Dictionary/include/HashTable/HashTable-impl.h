#ifndef HASHTABLE_HASHTABLE_IMPL_H
#define HASHTABLE_HASHTABLE_IMPL_H

#include "HashTable/HashTable.h"

#include <utility>
#include <iostream>

namespace puza {

template<typename Key, typename T>
HashTable<Key, T>::HashTable(size_t capacity) : size_(0), capacity_(capacity)
{
    array_ = new Node<std::pair<const Key, T>>*[capacity_ + 1] {nullptr};
}

template<typename Key, typename T>
HashTable<Key, T>::HashTable(const HashTable &obj) : size_(obj.size_), capacity_(obj.capacity_)
{
    array_ = new Node<std::pair<const Key, T>>*[capacity_ + 1];

    for (size_t i = 0; i < capacity_; i++)
    {
        if (obj.array_[i])
            array_[i] = new Node(*obj.array_[i]);
        else
            array_[i] = nullptr;
    }
}

template<typename Key, typename T>
HashTable<Key, T>::HashTable(HashTable &&obj) noexcept: size_(obj.size_), capacity_(obj.capacity_),
    array_(obj.array_)
{
    obj.array_ = nullptr;
}

template<typename Key, typename T>
HashTable<Key, T>::~HashTable()
{
    for (size_t i = 0; i < capacity_; i++)
    {
        delete_chain(array_[i]);
    }
    delete [] array_;
}

template<typename Key, typename T>
HashTable<Key, T> &HashTable<Key, T>::operator=(const HashTable &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    for (size_t i = 0; i < capacity_; i++)
    {
        delete_chain(array_[i]);
    }
    delete [] array_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;
    array_ = new Node<std::pair<const Key, T>>*[capacity_ + 1];

    for (size_t i = 0; i < capacity_; i++)
    {
        if (obj.array_[i])
            array_[i] = new Node(*obj.array_[i]);
        else
            array_[i] = nullptr;
    }

    return *this;
}

template<typename Key, typename T>
HashTable<Key, T> &HashTable<Key, T>::operator=(HashTable &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    for (size_t i = 0; i < capacity_; i++)
    {
        delete_chain(array_[i]);
    }
    delete [] array_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;
    array_ = obj.array;
    obj.array = nullptr;

    return *this;
}

template<typename Key, typename T>
bool HashTable<Key, T>::operator==(const HashTable &obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }
    if (empty())
    {
        return true;
    }

    for (size_t i = 0; i < capacity_; i++)
    {
        if ((array_[i] == nullptr) && (obj.array_[i] == nullptr))
            continue;

        if ((array_[i] == nullptr) || (obj.array_[i] == nullptr))
            return false;

        if (*array_[i] != *obj.array_[i])
            return false;
    }

    return true;
}

template<typename Key, typename T>
bool HashTable<Key, T>::operator!=(const HashTable &obj) const
{
    return !(*this == obj);
}

template<typename Key, typename T>
bool HashTable<Key, T>::empty() const
{
    return size_ == 0;
}

template<typename Key, typename T>
size_t HashTable<Key, T>::size() const
{
    return size_;
}

template<typename Key, typename T>
void HashTable<Key, T>::clear()
{
    for (size_t i = 0; i < capacity_; i++)
    {
        delete_chain(array_[i]);
        array_[i] = nullptr;
    }

    size_ = 0;
}

template<typename Key, typename T>
bool HashTable<Key, T>::insert(const Key &key, const T &value)
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];
    Node<std::pair<const Key, T>> *prev_node = current_node;

    while (current_node)
    {
        if (current_node->value.first == key)
            return false;
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    current_node = new Node<std::pair<const Key, T>>(std::make_pair(key, value));
    if (prev_node)
    {
        prev_node->next = current_node;
    }
    else
        array_[ind] = current_node;

    size_++;

    return true;
}

template<typename Key, typename T>
bool HashTable<Key, T>::insert_or_assign(const Key &key, const T &value)
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];
    Node<std::pair<const Key, T>> *prev_node = current_node;

    while (current_node)
    {
        if (current_node->value.first == key)
        {
            current_node->value.second = value;
            return false;
        }
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    current_node = new Node<std::pair<const Key, T>>(std::make_pair(key, value));
    if (prev_node)
    {
        prev_node->next = current_node;
    }
    else
        array_[ind] = current_node;
    
    size_++;

    return true;
}

template<typename Key, typename T>
bool HashTable<Key, T>::erase(const Key &key)
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];
    Node<std::pair<const Key, T>> *prev_node = current_node;

    while (current_node)
    {
        if (current_node->value.first == key)
        {
            if (current_node == array_[ind])
            {
                array_[ind] = current_node->next;
            }
            else
            {
                prev_node->next = current_node->next;
            }

            size_--;

            delete current_node;
            return true;
        }
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    return false;
}

template<typename Key, typename T>
void HashTable<Key, T>::swap(HashTable &obj)
{
    HashTable<Key, T> temp = std::move(*this);
    *this = std::move(obj);
    obj = std::move(temp);
}

template<typename Key, typename T>
T &HashTable<Key, T>::operator[](const Key& key)
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];
    Node<std::pair<const Key, T>> *prev_node = current_node;

    while (current_node)
    {
        if (current_node->value.first == key)
        {
            return current_node->value.second;
        }
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    current_node = new Node<std::pair<const Key, T>>(std::make_pair(key, T{}));
    if (prev_node)
    {
        prev_node->next = current_node;
    }
    else
        array_[ind] = current_node;
    
    size_++;

    return current_node->value.second;
}

template<typename Key, typename T>
T *HashTable<Key, T>::find(const Key& key)
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];

    while (current_node)
    {
        if (current_node->value.first == key)
        {
            return &current_node->value.second;
        }
        
        current_node = current_node->next;
    }

    return nullptr;
}

template<typename Key, typename T>
bool HashTable<Key, T>::contains(const Key& key) const
{
    size_t ind = Hash()(key).value % capacity_;
    Node<std::pair<const Key, T>> *current_node = array_[ind];

    while (current_node)
    {
        if (current_node->value.first == key)
        {
            return true;
        }
        
        current_node = current_node->next;
    }

    return false;
}

template<typename Key, typename T>
void HashTable<Key, T>::print()
{
    for (const auto& it : *this)
    {
        std::cout << "{" << it.value.first << "}{" << it.value.second << "}\n";
    }
}

template<typename Key, typename T>
HashTable<Key, T>::iterator::iterator(size_t index, Node<std::pair<const Key, T>> *pointer, const HashTable<Key, T> *ht) :
    index_(index), pointer_(pointer), ht_(ht)
{}

template<typename Key, typename T>
typename HashTable<Key, T>::iterator& HashTable<Key, T>::iterator::operator++()
{
    if (ht_->array_[index_])
    {
        if (pointer_ && pointer_->next)
        {
            pointer_ = pointer_->next;
            return *this;
        }
    }

    index_++;
    while ((index_ < ht_->capacity_ + 1) && (ht_->array_[index_++] == nullptr));
    index_--;
    pointer_ = ht_->array_[index_];

    return *this;
}

template<typename Key, typename T>
typename HashTable<Key, T>::iterator HashTable<Key, T>::iterator::operator++(int)
{
    iterator retval = *this;
    ++(*this);
    return retval;
}

template<typename Key, typename T>
bool HashTable<Key, T>::iterator::operator==(const iterator &obj) const
{
    return (index_ == obj.index_) && (pointer_ == obj.pointer_);
}

template<typename Key, typename T>
bool HashTable<Key, T>::iterator::operator!=(const iterator &obj) const
{
    return !(*this == obj);
}

template<typename Key, typename T>
Node<std::pair<const Key, T>>& HashTable<Key, T>::iterator::operator*() const
{
    return *pointer_;
}

template<typename Key, typename T>
Node<std::pair<const Key, T>>* HashTable<Key, T>::iterator::operator->() const
{
    return pointer_;
}

template<typename Key, typename T>
typename HashTable<Key, T>::iterator HashTable<Key, T>::begin()
{
    size_t index = 0;
    while ((index < capacity_) && (array_[index++] == nullptr));
    index--;
    return iterator(index, array_[index], this);
}

template<typename Key, typename T>
typename HashTable<Key, T>::iterator HashTable<Key, T>::end()
{
    return iterator(capacity_, array_[capacity_], this);
}

template<typename Key, typename T>
void HashTable<Key, T>::delete_chain(Node<std::pair<const Key, T>> *node)
{
    Node<std::pair<const Key, T>> *current_node = node;
    Node<std::pair<const Key, T>> *next_node = nullptr;

    while (current_node)
    {
        next_node = current_node->next;
        delete current_node;
        current_node = next_node;
    }
}

} // namespace puza

#endif // HASHTABLE_HASHTABLE_IMPL_H