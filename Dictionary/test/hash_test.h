#include "HashTable/HashTable-impl.h"

#include <gtest/gtest.h>

template<typename T>
class HashTest : public testing::Test
{
protected:
    using MyType = T;
    puza::HashTable<T, int> ht_;
    T val1_ = static_cast<T>(0);
    T val2_ = static_cast<T>(1);
    const size_t MAX_ITER_ = 1000000;
};

template<>
puza::Hash& puza::Hash::operator()(const int& data)
{
    return *this = Hash(static_cast<TYPE>(data));
}

typedef testing::Types<int> MyTypes;

TYPED_TEST_SUITE(HashTest, MyTypes, );

TYPED_TEST(HashTest, Empty)
{
    EXPECT_TRUE(this->ht_.empty());
    this->ht_.insert(this->val1_, 1);
    EXPECT_FALSE(this->ht_.empty());
}

TYPED_TEST(HashTest, Size)
{
    this->ht_.insert(this->val1_, 1);
    EXPECT_TRUE(this->ht_.size() == 1);
    this->ht_.insert(this->val1_, 1);
    EXPECT_TRUE(this->ht_.size() == 1);
    this->ht_.insert(this->val2_, 1);
    EXPECT_TRUE(this->ht_.size() == 2);
}

TYPED_TEST(HashTest, Clear)
{
    EXPECT_TRUE(this->ht_.empty());
    this->ht_.insert(this->val1_, 1);
    EXPECT_FALSE(this->ht_.empty());
    EXPECT_TRUE(this->ht_.size() == 1);
    this->ht_.clear();
    EXPECT_TRUE(this->ht_.empty());
}

TYPED_TEST(HashTest, Insert)
{
    using T = typename TestFixture::MyType;
    EXPECT_TRUE(this->ht_.empty());
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.insert(static_cast<T>(i), 1);
        EXPECT_TRUE(this->ht_.size() == i);
    }
}

TYPED_TEST(HashTest, InsertOrAssign)
{
    using T = typename TestFixture::MyType;
    EXPECT_TRUE(this->ht_.empty());
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.insert(static_cast<T>(i), 1);
        EXPECT_TRUE(this->ht_.size() == i);
    }
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.insert_or_assign(static_cast<T>(i), 2);
        EXPECT_TRUE(this->ht_.size() == this->MAX_ITER_);
    }
}

TYPED_TEST(HashTest, Erase)
{
    using T = typename TestFixture::MyType;
    EXPECT_TRUE(this->ht_.empty());
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.insert(static_cast<T>(i), 1);
        EXPECT_TRUE(this->ht_.size() == i);
    }
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.erase(static_cast<T>(i));
        EXPECT_TRUE(this->ht_.size() == this->MAX_ITER_ - i);
    }
}

TYPED_TEST(HashTest, Operator)
{
    using T = typename TestFixture::MyType;
    EXPECT_TRUE(this->ht_.empty());
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_[static_cast<T>(i)] = i;
        EXPECT_TRUE(this->ht_.size() == i);
        EXPECT_TRUE(this->ht_[static_cast<T>(i)] == i);
    }
}

TYPED_TEST(HashTest, Contains)
{
    using T = typename TestFixture::MyType;
    EXPECT_TRUE(this->ht_.empty());
    for (size_t i = 1; i <= this->MAX_ITER_; i++)
    {
        this->ht_.insert(static_cast<T>(i), 1);
        EXPECT_TRUE(this->ht_.contains(static_cast<T>(i)));
    }
}