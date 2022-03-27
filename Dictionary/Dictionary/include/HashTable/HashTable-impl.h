#ifndef HASHTABLE_HASHTABLE_IMPL_H
#define HASHTABLE_HASHTABLE_IMPL_H

#include "HashTable/HashTable.h"

namespace puza {

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::HashTable(size_t capacity) : capacity_(capacity)
{
    array_ = new List<Node> [capacity_];
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::HashTable(const HashTable& obj) : capacity_(obj.capacity_), iter_vec_(obj.iter_vec_)
{
    array_ = new List<Node> [capacity_];

    for (size_t i = 0; i < capacity_; i++)
    {
        array_[i] = List<Node>(obj.array_[i]);
    }
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::HashTable(HashTable&& obj) noexcept :
    capacity_(obj.capacity_), array_(obj.array_), iter_vec_(std::move(obj.iter_vec_))
{
    obj.array_ = nullptr;
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::~HashTable()
{
    delete[] array_;
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>& HashTable<Key, T, Hash>::operator=(const HashTable& obj)
{
    if (this == &obj)
        return *this;

    delete[] array_;

    capacity_ = obj.capacity_;
    iter_vec_ = obj.iter_vec_;
    array_ = new List<Node> [capacity_];

    for (size_t i = 0; i < capacity_; i++)
    {
        array_[i] = List<Node>(obj.array_[i]);
    }

    return *this;
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>& HashTable<Key, T, Hash>::operator=(HashTable&& obj) noexcept
{
    if (this == &obj)
        return *this;

    delete[] array_;

    capacity_ = obj.capacity_;
    array_ = obj.array_;
    iter_vec_ = std::move(obj.iter_vec_);
    obj.array_ = nullptr;

    return *this;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::operator==(const HashTable& obj) const
{
    if (size() != obj.size())
        return false;

    if (empty())
        return true;

    for (size_t i = 0; i < capacity_; i++)
    {
        if (array_[i] != obj.array_[i])
            return false;
    }

    return true;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::operator!=(const HashTable& obj) const
{
    return !(*this == obj);
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::empty() const
{
    return iter_vec_.empty();
}

template<typename Key, typename T, typename Hash>
size_t HashTable<Key, T, Hash>::size() const
{
    return iter_vec_.size();
}

template<typename Key, typename T, typename Hash>
size_t HashTable<Key, T, Hash>::capacity() const
{
    return capacity_;
}

template<typename Key, typename T, typename Hash>
void HashTable<Key, T, Hash>::clear()
{
    iter_vec_.clear();
    for (size_t i = 0; i < capacity_; i++)
    {
        array_[i].clear();
    }
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::insert(const Key& key, const T& value)
{
    size_t ind = Hash()(key) % capacity_;

    for (const auto& it : array_[ind])
    {
        if (it.key == key)
            return false;
    }

    iter_vec_.push_back(nullptr);
    array_[ind].push_back(Node(key, value));
    iter_vec_.back() = &array_[ind].back();

    return true;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::insert_or_assign(const Key& key, const T& value)
{
    size_t ind = Hash()(key) % capacity_;

    for (auto& it : array_[ind])
    {
        if (it.key == key)
        {
            it.value = value;
            return false;
        }
    }

    iter_vec_.push_back(nullptr);
    array_[ind].push_back(Node(key, value));
    iter_vec_.back() = &array_[ind].back();

    return true;
}

template<typename Key, typename T, typename Hash>
T& HashTable<Key, T, Hash>::operator[](const Key& key)
{
    size_t ind = Hash()(key) % capacity_;

    for (auto& it : array_[ind])
    {
        if (it.key == key)
            return it.value;
    }

    iter_vec_.push_back(nullptr);
    array_[ind].push_back(Node(key, T()));
    iter_vec_.back() = &array_[ind].back();

    return array_[ind].back().value;
}

template<typename Key, typename T, typename Hash>
T* HashTable<Key, T, Hash>::find(const Key& key)
{
    size_t ind = Hash()(key) % capacity_;

    for (auto& it : array_[ind])
    {
        if (it.key == key)
            return &it.value;
    }

    return nullptr;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::contains(const Key& key) const
{
    size_t ind = Hash()(key) % capacity_;

    for (auto& it : array_[ind])
    {
        if (it.key == key)
            return true;
    }

    return false;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::begin()
{
    return iterator(iter_vec_.begin());
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::end()
{
    return iterator(iter_vec_.end());
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator HashTable<Key, T, Hash>::begin() const
{
    return const_iterator(iter_vec_.begin());
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator HashTable<Key, T, Hash>::end() const
{
    return const_iterator(iter_vec_.end());
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::iterator::iterator(const vec_iter& it) : it_(it) {}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator& HashTable<Key, T, Hash>::iterator::operator++()
{
    ++it_;
    return *this;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator::operator++(int)
{
    iterator retval = *this;
    it_++;
    return retval;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator& HashTable<Key, T, Hash>::iterator::operator--()
{
    --it_;
    return *this;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::iterator HashTable<Key, T, Hash>::iterator::operator--(int)
{
    iterator retval = *this;
    it_--;
    return retval;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::iterator::operator==(const iterator& obj) const
{
    return it_ == obj.it_;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::iterator::operator!=(const iterator& obj) const
{
    return it_ != obj.it_;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::Node& HashTable<Key, T, Hash>::iterator::operator*()
{
    return **it_;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::Node* HashTable<Key, T, Hash>::iterator::operator->()
{
    return *it_;
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::const_iterator::const_iterator(const vec_const_iter& it) : it_(it) {}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator& HashTable<Key, T, Hash>::const_iterator::operator++()
{
    ++it_;
    return *this;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator HashTable<Key, T, Hash>::const_iterator::operator++(int)
{
    iterator retval = *this;
    it_++;
    return retval;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator& HashTable<Key, T, Hash>::const_iterator::operator--()
{
    --it_;
    return *this;
}

template<typename Key, typename T, typename Hash>
typename HashTable<Key, T, Hash>::const_iterator HashTable<Key, T, Hash>::const_iterator::operator--(int)
{
    iterator retval = *this;
    it_--;
    return retval;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::const_iterator::operator==(const const_iterator& obj) const
{
    return it_ == obj.it_;
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::const_iterator::operator!=(const const_iterator& obj) const
{
    return it_ != obj.it_;
}

template<typename Key, typename T, typename Hash>
const typename HashTable<Key, T, Hash>::Node& HashTable<Key, T, Hash>::const_iterator::operator*() const
{
    return **it_;
}

template<typename Key, typename T, typename Hash>
const typename HashTable<Key, T, Hash>::Node* HashTable<Key, T, Hash>::const_iterator::operator->() const
{
    return *it_;
}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::Node::Node(const Key& k, const T& val) :
    key(k), value(val)
{}

template<typename Key, typename T, typename Hash>
HashTable<Key, T, Hash>::Node::Node(const Node& obj) :
    key(obj.key), value(obj.value)
{}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::Node::operator==(const Node& obj) const
{
    return (key == obj.key) && (value == obj.value);
}

template<typename Key, typename T, typename Hash>
bool HashTable<Key, T, Hash>::Node::operator!=(const Node& obj) const
{
    return !(*this == obj);
}

} // namespace puza

#endif // HASHTABLE_HASHTABLE_IMPL_H