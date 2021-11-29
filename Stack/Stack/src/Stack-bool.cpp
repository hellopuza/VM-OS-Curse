#include "Stack/Stack.h"

#include <utility>

namespace puza {

Stack<bool>::Stack() : size_(0), capacity_(DEFAULT_CAPACITY)
{
    data_ = new char[capacity_ / 8 + 1];
}

Stack<bool>::Stack(float grow_factor) : grow_factor_(grow_factor), size_(0), capacity_(DEFAULT_CAPACITY)
{
    data_ = new char[capacity_ / 8 + 1];
}

Stack<bool>::Stack(size_t size, const bool *data) : size_(size), capacity_(size)
{
    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i < size_; i++)
    {
        data_[i / 8] &= static_cast<char>(~(1 << (i % 8)));
        data_[i / 8] ^= static_cast<char>(static_cast<char>(data[i]) << (i % 8));
    }
}

Stack<bool>::~Stack()
{
    delete[] data_;
}

Stack<bool>::Stack(const Stack &obj) : size_(obj.size_), capacity_(obj.capacity_)
{
    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i <= size_ / 8; i++) { data_[i] = obj.data_[i]; }
}

Stack<bool>::Stack(Stack &&obj) noexcept : size_(obj.size_), capacity_(obj.capacity_), data_(obj.data_)
{
    obj.data_ = nullptr;
}

Stack<bool> &Stack<bool>::operator=(const Stack &obj)
{
    if (this == &obj)
    {
        return *this;
    }

    delete[] data_;

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    data_ = new char[capacity_ / 8 + 1];
    for (size_t i = 0; i <= size_ / 8; i++) { data_[i] = obj.data_[i]; }

    return *this;
}

Stack<bool> &Stack<bool>::operator=(Stack &&obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }

    size_ = obj.size_;
    capacity_ = obj.capacity_;

    delete[] data_;
    data_ = obj.data_;
    obj.data_ = nullptr;

    return *this;
}

bool Stack<bool>::operator==(const Stack &obj) const
{
    if (size_ != obj.size_)
    {
        return false;
    }

    for (size_t i = 0; i < size_; i++)
    {
        if (((data_[i / 8] >> static_cast<char>(i % 8)) & 1) != ((obj.data_[i / 8] >> static_cast<char>(i % 8)) & 1))
        {
            return false;
        }
    }
    return true;
}

bool Stack<bool>::operator!=(const Stack &obj) const
{
    return !(*this == obj);
}

void Stack<bool>::push(bool value)
{
    if (size_ == capacity_)
    {
        expand();
    }

    data_[size_ / 8] &= static_cast<char>(~(1 << (size_ % 8)));
    data_[size_ / 8] ^= static_cast<char>(static_cast<char>(value) << (size_ % 8));
    size_++;
}

bool Stack<bool>::top() const
{
    return static_cast<bool>(data_[(size_ - 1) / 8] & (1 << ((size_ - 1) % 8)));
}

void Stack<bool>::pop()
{
    --size_;
}

void Stack<bool>::swap(Stack *obj)
{
    Stack<bool> temp = std::move(*this);
    *this = std::move(*obj);
    *obj = std::move(temp);
}

size_t Stack<bool>::size() const
{
    return size_;
}

bool Stack<bool>::empty() const
{
    return size_ == 0;
}

void Stack<bool>::expand()
{
    capacity_ = static_cast<size_t>(static_cast<float>(capacity_) * grow_factor_);
    char *temp = new char[capacity_ / 8 + 1];

    for (size_t i = 0; i <= size_ / 8; i++) { temp[i] = data_[i]; }

    delete[] data_;
    data_ = temp;
}

} // namespace puza