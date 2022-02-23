#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "HashTable/Node-impl.h"
#include "HashTable/Hash.h"
#include <algorithm>
#include <cstdlib>
#include <utility>

namespace puza {

template<typename Key, typename T>
class HashTable
{
public:
    explicit HashTable(size_t capacity = DEFAULT_CAPACITY_);
    HashTable(const HashTable &obj);
    HashTable(HashTable &&obj) noexcept;
    ~HashTable();

    HashTable &operator=(const HashTable &obj);
    HashTable &operator=(HashTable &&obj) noexcept;
    bool operator==(const HashTable &obj) const;
    bool operator!=(const HashTable &obj) const;

    bool empty() const;
    size_t size() const;
    void clear();

    bool insert(const Key &key, const T &value);
    bool insert_or_assign(const Key &key, const T &value);
    bool erase(const Key &key);
    void swap(HashTable &obj);

    T &operator[](const Key& key);
    T *find(const Key& key);
    bool contains(const Key& key) const;

    void print();

    class iterator;
    iterator begin();
    iterator end();

    static const size_t DEFAULT_CAPACITY_ = 1 << 22;

private:
    void delete_chain(Node<std::pair<const Key, T>> *node);

    size_t size_;
    size_t capacity_;
    Node<std::pair<const Key, T>> **array_;
};

template<typename Key, typename T>
class HashTable<Key, T>::iterator
{
public:
    iterator(size_t index, Node<std::pair<const Key, T>> *pointer, const HashTable<Key, T> *ht);
    iterator &operator++();
    iterator operator++(int);
    bool operator==(const iterator &obj) const;
    bool operator!=(const iterator &obj) const;
    Node<std::pair<const Key, T>>& operator*() const;
    Node<std::pair<const Key, T>>* operator->() const;

private:
    size_t index_;
    Node<std::pair<const Key, T>> *pointer_;
    const HashTable<Key, T> *ht_;
};

} // namespace puza

#endif // HASHTABLE_HASHTABLE_H