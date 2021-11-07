#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <cstdlib>

namespace puza {

template<typename T>
class Queue
{
public:
    Queue();
    Queue(size_t size, const T *data);
    Queue(const Queue &obj);
    Queue(Queue &&obj) noexcept;
    ~Queue();

    Queue &operator=(const Queue &obj);
    Queue &operator=(Queue &&obj) noexcept;

    bool operator==(const Queue &obj) const;
    bool operator!=(const Queue &obj) const;

    void push(const T &value);
    void pop();

    const T &front() const;
    const T &back() const;
    T &front();
    T &back();

    void swap(Queue *obj);
    bool empty() const;
    size_t size() const;

private:
    void delete_nodes();

    struct Node
    {
        T data;
        Node *next;
    } *front_, *back_;

    size_t size_;
};

} // namespace puza

#endif // QUEUE_QUEUE_H