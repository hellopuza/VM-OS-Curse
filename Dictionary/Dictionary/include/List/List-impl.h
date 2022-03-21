#ifndef LIST_IMPL_LIST_IMPL_H
#define LIST_IMPL_LIST_IMPL_H

#include "List/List.h"

#include <utility>

namespace puza {

template<typename T>
List<T>::List() : size_(0) {}

template<typename T>
List<T>::List(const List& obj) : size_(obj.size_)
{
    if (obj.front_)
    {
        front_ = new Node;

        *front_ = *obj.front_;
        back_ = front_;
        while (back_->next)
        {
            back_ = back_->next;
        }
    }
}

template<typename T>
List<T>::List(List&& obj) noexcept : size_(obj.size_), front_(obj.front_), back_(obj.back_)
{
    obj.front_ = nullptr;
    obj.back_ = nullptr;
}

template<typename T>
List<T>::~List()
{
    if (front_)
    {
        front_->delete_next_chain();
        delete front_;
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& obj)
{
    if (this == &obj)
        return *this;

    size_ = obj.size_;

    if (front_)
    {
        front_->delete_next_chain();
        delete front_;
    }

    front_ = new Node;
    *front_ = *obj.front_;

    back_ = front_;
    while (back_->next)
    {
        back_ = back_->next;
    }

    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& obj) noexcept
{
    if (this == &obj)
        return *this;

    if (front_)
    {
        front_->delete_next_chain();
        delete front_;
    }

    size_ = obj.size_;
    front_ = obj.front_;
    back_ = obj.back_;

    obj.front_ = nullptr;
    obj.back_ = nullptr;

    return *this;
}

template<typename T>
bool List<T>::operator==(const List& obj) const
{
    if (size_ != obj.size_)
        return false;

    if (empty())
        return true;

    return *front_ == *obj.front_;
}

template<typename T>
bool List<T>::operator!=(const List& obj) const
{
    return !(*this == obj);
}

template<typename T>
void List<T>::push_front(const T& value)
{
    Node* next = front_;
    front_ = new Node(value);
    front_->next = next;

    if (next)
        next->prev = front_;
    else
        back_ = front_;

    size_++;
}

template<typename T>
void List<T>::push_back(const T& value)
{
    Node* prev = back_;
    back_ = new Node(value);
    back_->prev = prev;

    if (prev)
        prev->next = back_;
    else
        front_ = back_;

    size_++;
}

template<typename T>
void List<T>::pop_front()
{
    Node* next = front_->next;
    delete front_;

    if (next)
    {
        front_ = next;
        front_->prev = nullptr;
    }
    else
    {
        front_ = nullptr;
        back_ = nullptr;
    }
    size_--;
}

template<typename T>
void List<T>::pop_back()
{
    Node* prev = back_->prev;
    delete back_;

    if (prev)
    {
        back_ = prev;
        back_->next = nullptr;
    }
    else
    {
        front_ = nullptr;
        back_ = nullptr;
    }
    size_--;
}

template<typename T>
const T& List<T>::front() const
{
    return front_->value;
}

template<typename T>
const T& List<T>::back() const
{
    return back_->value;
}

template<typename T>
T& List<T>::front()
{
    return front_->value;
}

template<typename T>
T& List<T>::back()
{
    return back_->value;
}

template<typename T>
bool List<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
size_t List<T>::size() const
{
    return size_;
}

template<typename T>
void List<T>::clear()
{
    if (front_)
    {
        front_->delete_next_chain();
        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }
}

template<typename T>
void List<T>::erase(iterator it)
{
    if (it.ptr_ == front_)
    {
        pop_front();
        return;
    }

    if (it.ptr_ == back_)
    {
        pop_back();
        return;
    }

    it.ptr_->next->prev = it.ptr_->prev;
    it.ptr_->prev->next = it.ptr_->next;
    delete it.ptr_;
}

template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(front_);
}

template<typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator(nullptr);
}

template<typename T>
typename List<T>::iterator List<T>::end_iter()
{
    return iterator(back_);
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(front_);
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(nullptr);
}

template<typename T>
typename List<T>::const_iterator List<T>::end_iter() const
{
    return const_iterator(back_);
}

template<typename T>
List<T>::iterator::iterator(Node* ptr) : ptr_(ptr) {}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    ptr_ = ptr_->next;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator retval = *this;
    ++(*this);
    return retval;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    ptr_ = ptr_->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator retval = *this;
    --(*this);
    return retval;
}

template<typename T>
bool List<T>::iterator::operator==(const iterator& obj) const
{
    return ptr_ == obj.ptr_;
}

template<typename T>
bool List<T>::iterator::operator!=(const iterator& obj) const
{
    return ptr_ != obj.ptr_;
}

template<typename T>
T& List<T>::iterator::operator*()
{
    return ptr_->value;
}

template<typename T>
T* List<T>::iterator::operator->()
{
    return &ptr_->value;
}

template<typename T>
List<T>::const_iterator::const_iterator(Node* ptr) : ptr_(ptr) {}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    ptr_ = ptr_->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator retval = *this;
    ++(*this);
    return retval;
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    ptr_ = ptr_->prev;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator retval = *this;
    --(*this);
    return retval;
}

template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator& obj) const
{
    return ptr_ == obj.ptr_;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& obj) const
{
    return ptr_ != obj.ptr_;
}

template<typename T>
const T& List<T>::const_iterator::operator*() const
{
    return ptr_->value;
}

template<typename T>
const T* List<T>::const_iterator::operator->() const
{
    return &ptr_->value;
}

template<typename T>
List<T>::Node::Node(const T& val) : value(val)
{}

template<typename T>
List<T>::Node::Node(const Node& obj)
{
    Node* current_node = this;
    current_node->value = obj.value;
    current_node->next = nullptr;
    Node* obj_node = obj.next;

    while (obj_node)
    {
        current_node->next = new Node;
        current_node->next->prev = current_node;
        current_node = current_node->next;
        current_node->value = obj_node->value;

        obj_node = obj_node->next;
    }
}

template<typename T>
List<T>::Node::Node(Node&& obj) noexcept : value(obj.value), next(obj.next)
{
    obj.next = nullptr;
}

template<typename T>
typename List<T>::Node& List<T>::Node::operator=(const Node& obj)
{
    if (this == &obj)
        return *this;

    delete_next_chain();

    Node* current_node = this;
    current_node->value = obj.value;
    current_node->next = nullptr;
    Node* obj_node = obj.next;

    while (obj_node)
    {
        current_node->next = new Node;
        current_node->next->prev = current_node;
        current_node = current_node->next;
        current_node->value = obj_node->value;

        obj_node = obj_node->next;
    }

    return *this;
}

template<typename T>
typename List<T>::Node& List<T>::Node::operator=(Node&& obj) noexcept
{
    if (this == &obj)
        return *this;

    delete_next_chain();

    value = obj.value;
    next = obj.next;
    obj.next = nullptr;

    return *this;
}

template<typename T>
bool List<T>::Node::operator==(const Node& obj) const
{
    Node* current_node = const_cast<Node*>(this);
    Node* obj_node = const_cast<Node*>(&obj);

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
bool List<T>::Node::operator!=(const Node& obj) const
{
    return !(*this == obj);
}

template<typename T>
void List<T>::Node::delete_next_chain()
{
    Node* current_node = next;
    Node* next_node = nullptr;

    while (current_node)
    {
        next_node = current_node->next;
        delete current_node;
        current_node = next_node;
    }
    next = nullptr;
}

} // namespace puza

#endif // LIST_IMPL_LIST_IMPL_H