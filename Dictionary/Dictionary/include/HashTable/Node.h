#ifndef HASHTABLE_NODE_H
#define HASHTABLE_NODE_H

#include <cstdlib>

namespace puza {

template<typename T>
struct Node
{
    T value;
    Node *next = nullptr;

    Node() = default;
    explicit Node(const T &val);
    Node(const Node &obj);
    Node(Node &&obj) noexcept;
    ~Node() = default;

    Node &operator=(const Node &obj);
    Node &operator=(Node &&obj) noexcept;
    bool operator==(const Node &obj) const;
    bool operator!=(const Node &obj) const;
};

} // namespace puza

#endif // HASHTABLE_NODE_H