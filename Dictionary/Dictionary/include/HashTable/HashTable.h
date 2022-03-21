#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "List/List-impl.h"

#include <cstdlib>
#include <functional>

namespace puza {

template<typename Key, typename T, typename Hash = std::hash<Key>>
class HashTable
{
public:
    explicit HashTable(size_t capacity = DEFAULT_CAPACITY_);
    HashTable(const HashTable& obj);
    HashTable(HashTable&& obj) noexcept;
    virtual ~HashTable();

    HashTable& operator=(const HashTable &obj);
    HashTable& operator=(HashTable&& obj) noexcept;
    bool operator==(const HashTable& obj) const;
    bool operator!=(const HashTable& obj) const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void clear();

    bool insert(const Key& key, const T& value);
    bool insert_or_assign(const Key& key, const T& value);
    bool erase(const Key& key);

    T& operator[](const Key& key);
    T* find(const Key& key);
    bool contains(const Key& key) const;

    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    static const size_t DEFAULT_CAPACITY_ = 1 << 16;

    struct Node;

private:
    using list_iter = typename List<Node*>::iterator;
    using list_const_iter = typename List<Node*>::const_iterator;

    size_t capacity_;
    List<Node>* array_;
    List<Node*> iter_list_;
};

template<typename Key, typename T, typename Hash>
class HashTable<Key, T, Hash>::iterator final
{
public:
    iterator() = default;
    explicit iterator(const list_iter& it);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& obj) const;
    bool operator!=(const iterator& obj) const;
    Node& operator*();
    Node* operator->();

private:
    list_iter it_;
};

template<typename Key, typename T, typename Hash>
class HashTable<Key, T, Hash>::const_iterator final
{
public:
    const_iterator() = default;
    explicit const_iterator(const list_const_iter& it);
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator& obj) const;
    bool operator!=(const const_iterator& obj) const;
    const Node& operator*() const;
    const Node* operator->() const;

private:
    list_const_iter it_;
};

template<typename Key, typename T, typename Hash>
struct HashTable<Key, T, Hash>::Node final
{
    Node() = default;
    Node(const Key& k, const T& val, const list_iter& iter);
    Node(const Node& obj);
    Node(Node&& obj) noexcept = default;
    ~Node() = default;

    Node& operator=(const Node& obj) = default;
    Node& operator=(Node&& obj) noexcept = default;
    bool operator==(const Node& obj) const;
    bool operator!=(const Node& obj) const;

    Key key;
    T value;
    list_iter it;
};

} // namespace puza

#endif // HASHTABLE_HASHTABLE_H