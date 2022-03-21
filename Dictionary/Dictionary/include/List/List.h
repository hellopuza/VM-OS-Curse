#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <cstdlib>

namespace puza {

template<typename T>
class List final
{
public:
    List();
    List(const List& obj);
    List(List&& obj) noexcept;
    ~List();

    List& operator=(const List &obj);
    List& operator=(List&& obj) noexcept;
    bool operator==(const List& obj) const;
    bool operator!=(const List& obj) const;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    const T& front() const;
    const T& back() const;
    T& front();
    T& back();

    bool empty() const;
    size_t size() const;
    void clear();

    class iterator;
    class const_iterator;

    void erase(iterator it);

    iterator begin();
    iterator end();
    iterator end_iter();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator end_iter() const;

private:
    struct Node;

    size_t size_;
    Node* front_ = nullptr;
    Node* back_ = nullptr;
};

template<typename T>
class List<T>::iterator final
{
public:
    iterator() = default;
    explicit iterator(Node* ptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& obj) const;
    bool operator!=(const iterator& obj) const;
    T& operator*();
    T* operator->();

private:
    friend class List<T>;

    Node* ptr_ = nullptr;
};

template<typename T>
class List<T>::const_iterator final
{
public:
    const_iterator() = default;
    explicit const_iterator(Node* ptr);
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator& obj) const;
    bool operator!=(const const_iterator& obj) const;
    const T& operator*() const;
    const T* operator->() const;

private:
    friend class List<T>;

    Node* ptr_ = nullptr;
};

template<typename T>
struct List<T>::Node final
{
    Node() = default;
    explicit Node(const T& val);
    Node(const Node& obj);
    Node(Node&& obj) noexcept;
    ~Node() = default;

    Node &operator=(const Node& obj);
    Node &operator=(Node&& obj) noexcept;
    bool operator==(const Node& obj) const;
    bool operator!=(const Node& obj) const;

    void delete_next_chain();

    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
};

} // namespace puza

#endif // LIST_LIST_H