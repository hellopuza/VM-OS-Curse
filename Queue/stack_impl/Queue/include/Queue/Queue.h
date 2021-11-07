#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include "Stack/Stack-impl.h"

namespace puza {

template<typename T>
class Queue
{
public:
    Queue() = default;
    Queue(size_t size, const T *data);
    Queue(const Queue &obj) = default;
    Queue(Queue &&obj) noexcept;
    ~Queue() = default;

    Queue &operator=(const Queue &obj);
    Queue &operator=(Queue &&obj) noexcept;

    bool operator==(const Queue &obj) const;
    bool operator!=(const Queue &obj) const;

    void push(const T &value);
    void pop();

    const T &back() const;
    T &front();
    T &back();

    void swap(Queue *obj);
    bool empty() const;
    size_t size() const;

private:
    void move_elements();

    Stack<T> pop_stk_;
    Stack<T> push_stk_;
};

template<>
class Queue<bool>
{
public:
    Queue() = default;
    Queue(size_t size, const bool *data);
    Queue(const Queue &obj) = default;
    Queue(Queue &&obj) noexcept;
    ~Queue() = default;

    Queue &operator=(const Queue &obj);
    Queue &operator=(Queue &&obj) noexcept;

    bool operator==(const Queue &obj) const;
    bool operator!=(const Queue &obj) const;

    void push(bool value);
    void pop();

    bool front();
    bool back() const;

    void swap(Queue *obj);
    bool empty() const;
    size_t size() const;

private:
    void move_elements();

    Stack<bool> pop_stk_;
    Stack<bool> push_stk_;
};

} // namespace puza

#endif // QUEUE_QUEUE_H