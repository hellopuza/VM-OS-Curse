#ifndef QUEUE_QUEUE_IMPL_H
#define QUEUE_QUEUE_IMPL_H

#include "Queue/Queue.h"

#include <utility>

namespace puza {

template<typename T>
Queue<T>::Queue(size_t size, const T *data) : push_stk_(size, data)
{}

template<typename T>
Queue<T>::Queue(Queue &&obj) noexcept : pop_stk_(std::move(obj.pop_stk_)), push_stk_(std::move(obj.push_stk_))
{}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    pop_stk_ = obj.pop_stk_;
    push_stk_ = obj.push_stk_;

    return *this;
}

template<typename T>
Queue<T> &Queue<T>::operator=(Queue &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    pop_stk_ = std::move(obj.pop_stk_);
    push_stk_ = std::move(obj.push_stk_);

    return *this;
}

template<typename T>
bool Queue<T>::operator==(const Queue &obj) const
{
    return (pop_stk_ == obj.pop_stk_) && (push_stk_ == obj.push_stk_);
}

template<typename T>
bool Queue<T>::operator!=(const Queue &obj) const
{
    return (pop_stk_ != obj.pop_stk_) || (push_stk_ != obj.push_stk_);
}

template<typename T>
void Queue<T>::push(const T &value)
{
    push_stk_.push(value);
}

template<typename T>
void Queue<T>::pop()
{
    if (pop_stk_.empty() && (push_stk_.size() == 1))
    {
        push_stk_.pop();
        return;
    }

    move_elements();
    pop_stk_.pop();
}

template<typename T>
T &Queue<T>::front()
{
    if (pop_stk_.empty() && (push_stk_.size() == 1))
    {
        return push_stk_.top();
    }

    move_elements();
    return pop_stk_.top();
}

template<typename T>
T &Queue<T>::back()
{
    return push_stk_.top();
}

template<typename T>
const T &Queue<T>::back() const
{
    return push_stk_.top();
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
    return pop_stk_.size() + push_stk_.size();
}

template<typename T>
bool Queue<T>::empty() const
{
    return pop_stk_.size() + push_stk_.size() == 0;
}

template<typename T>
void Queue<T>::move_elements()
{
    if (pop_stk_.empty())
    {
        T last_elem = push_stk_.top();
        push_stk_.pop();
        while (!push_stk_.empty())
        {
            pop_stk_.push(push_stk_.top());
            push_stk_.pop();
        }
        push_stk_.push(last_elem);
    }
}

} // namespace puza

#endif // QUEUE_QUEUE_IMPL_H