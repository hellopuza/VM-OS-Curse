#ifndef HASHTABLE_NODE_IMPL_H
#define HASHTABLE_NODE_IMPL_H

#include "HashTable/Node.h"

#include <utility>

namespace puza {

template<typename T>
Node<T>::Node(const T &val) : value(val)
{}

template<typename T>
Node<T>::Node(const Node &obj)
{
    Node *current_node = this;
    Node *obj_node = &obj;

    while (true)
    {
        current_node->value = obj_node->value;
        obj_node = obj_node->next;

        if (obj_node)
            current_node = current_node->next = new Node;
        else
            break;
    }
}

template<typename T>
Node<T>::Node(Node &&obj) noexcept : value(obj.value), next(obj.next)
{
    obj.next = nullptr;
}

template<typename T>
Node<T> &Node<T>::operator=(const Node &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete next;

    Node *current_node = this;
    Node *obj_node = &obj;

    while (true)
    {
        current_node->value = obj_node->value;
        obj_node = obj_node->next;

        if (obj_node)
            current_node = current_node->next = new Node;
        else
            break;
    }

    return *this;
}

template<typename T>
Node<T> &Node<T>::operator=(Node &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    delete next;

    value = obj.value;
    next = obj.next;
    obj.next = nullptr;

    return *this;
}

template<typename T>
bool Node<T>::operator==(const Node &obj) const
{
    Node *current_node = this;
    Node *obj_node = &obj;

    while (true)
    {
        if (current_node->value != obj_node->value)
            return false;
        
        current_node = current_node->next;
        obj_node = obj_node->next;

        if ((current_node == nullptr) && (obj_node == nullptr))
            break;
        
        if ((current_node == nullptr) || (obj_node == nullptr))
            return false;
    }
    
    return true;
}

template<typename T>
bool Node<T>::operator!=(const Node &obj) const
{
    return !(*this == obj);
}

} // namespace puza

#endif // HASHTABLE_NODE_IMPL_H