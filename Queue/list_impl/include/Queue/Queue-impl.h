#ifndef QUEUE_QUEUE_IMPL_H
#define QUEUE_QUEUE_IMPL_H

#include "Queue/Queue.h"

#include <utility>

namespace puza {

template<typename T>
Queue<T>::Queue() : front_(nullptr), back_(nullptr), size_(0)
{}

template<typename T>
Queue<T>::Queue(size_t size, const T *data) : size_(size)
{
    front_ = new Node;
    Node *current_node = front_;
    for (size_t i = 0; i < size; i++)
    {
        current_node->data = data[i];
        if (i != size - 1)
        {
            current_node->next = new Node;
            current_node = current_node->next;
        }
    }
    back_ = current_node;
}

template<typename T>
Queue<T>::Queue(const Queue &obj) : size_(obj.size_)
{
    if (!empty())
    {
        front_ = new Node;
        Node *current_node = front_;
        Node *obj_node = obj.front_;

        while (obj_node != obj.back_)
        {
            current_node->data = obj_node->data;
            current_node->next = new Node;
            current_node = current_node->next;
            obj_node = obj_node->next;
        }
        current_node->data = obj_node->data;
        back_ = current_node;
    }
    else
    {
        front_ = back_ = nullptr;
    }
}

template<typename T>
Queue<T>::Queue(Queue &&obj) noexcept : size_(obj.size_)
{
    front_ = obj.front_;
    back_ = obj.back_;

    obj.front_ = nullptr;
    obj.back_ = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
    delete_nodes();
}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete_nodes();
    size_ = obj.size_;

    if (!obj.empty())
    {
        front_ = new Node;
        Node *current_node = front_;
        Node *obj_node = obj.front_;

        while (obj_node != obj.back_)
        {
            current_node->data = obj_node->data;
            current_node->next = new Node;
            current_node = current_node->next;
            obj_node = obj_node->next;
        }
        current_node->data = obj_node->data;
        back_ = current_node;
    }
    else
    {
        front_ = back_ = nullptr;
    }

    return *this;
}

template<typename T>
Queue<T> &Queue<T>::operator=(Queue &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    delete_nodes();
    size_ = obj.size_;

    front_ = obj.front_;
    back_ = obj.back_;

    obj.front_ = nullptr;
    obj.back_ = nullptr;

    return *this;
}

template<typename T>
bool Queue<T>::operator==(const Queue &obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }
    if (empty())
    {
        return true;
    }

    Node *current_node = front_;
    Node *obj_node = obj.front_;

    while (obj_node != obj.back_)
    {
        if (current_node->data != obj_node->data)
        {
            return false;
        }
        current_node = current_node->next;
        obj_node = obj_node->next;
    }

    return current_node->data == obj_node->data;
}

template<typename T>
bool Queue<T>::operator!=(const Queue &obj) const
{
    return !(*this == obj);
}

template<typename T>
void Queue<T>::push(const T &value)
{
    if (empty())
    {
        front_ = back_ = new Node;
    }
    else
    {
        back_->next = new Node;
        back_ = back_->next;
    }
    back_->data = value;
    size_++;
}

template<typename T>
void Queue<T>::pop()
{
    if (size_ == 1)
    {
        delete front_;
        front_ = back_ = nullptr;
    }
    else
    {
        Node *next_node = front_->next;
        delete front_;
        front_ = next_node;
    }
    size_--;
}

template<typename T>
const T &Queue<T>::front() const
{
    return front_->data;
}

template<typename T>
T &Queue<T>::front()
{
    return front_->data;
}

template<typename T>
const T &Queue<T>::back() const
{
    return back_->data;
}

template<typename T>
T &Queue<T>::back()
{
    return back_->data;
}

template<typename T>
void Queue<T>::swap(Queue *obj)
{
    Queue<T> temp = std::move(*this);
    *this = std::move(*obj);
    *obj = std::move(temp);
}

template<typename T>
size_t Queue<T>::size() const
{
    return size_;
}

template<typename T>
bool Queue<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
void Queue<T>::delete_nodes()
{
    Node *current_node = front_;
    while (current_node != back_)
    {
        Node *next_node = current_node->next;
        delete current_node;
        current_node = next_node;
    }
    delete current_node;
}

} // namespace puza

#endif // QUEUE_QUEUE_IMPL_H