#include "Queue/Queue.h"

#include <utility>

namespace puza {

Queue<bool>::Queue(size_t size, const bool *data) : push_stk_(size, data) {}

Queue<bool>::Queue(Queue &&obj) noexcept : pop_stk_(std::move(obj.pop_stk_)), push_stk_(std::move(obj.push_stk_)) {}

Queue<bool> &Queue<bool>::operator=(const Queue &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    pop_stk_ = obj.pop_stk_;
    push_stk_ = obj.push_stk_;

    return *this;
}

Queue<bool> &Queue<bool>::operator=(Queue &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    pop_stk_ = std::move(obj.pop_stk_);
    push_stk_ = std::move(obj.push_stk_);

    return *this;
}

bool Queue<bool>::operator==(const Queue &obj) const
{
    return (pop_stk_ == obj.pop_stk_) && (push_stk_ == obj.push_stk_);
}

bool Queue<bool>::operator!=(const Queue &obj) const
{
    return (pop_stk_ != obj.pop_stk_) || (push_stk_ != obj.push_stk_);
}

void Queue<bool>::push(bool value)
{
    push_stk_.push(value);
}

void Queue<bool>::pop()
{
    if (pop_stk_.empty() && (push_stk_.size() == 1))
    {
        push_stk_.pop();
        return;
    }

    move_elements();
    pop_stk_.pop();
}

bool Queue<bool>::front()
{
    if (pop_stk_.empty() && (push_stk_.size() == 1))
    {
        return push_stk_.top();
    }

    move_elements();
    return pop_stk_.top();
}

bool Queue<bool>::back() const
{
    return push_stk_.top();
}

void Queue<bool>::swap(Queue *obj)
{
    Queue<bool> temp = std::move(*this);
    *this = std::move(*obj);
    *obj = std::move(temp);
}

size_t Queue<bool>::size() const
{
    return pop_stk_.size() + push_stk_.size();
}

bool Queue<bool>::empty() const
{
    return pop_stk_.size() + push_stk_.size() == 0;
}

void Queue<bool>::move_elements()
{
    if (pop_stk_.empty())
    {
        bool last_elem = push_stk_.top();
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