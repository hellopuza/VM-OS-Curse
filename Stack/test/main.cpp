#include <gtest/gtest.h>

#include "Stack-impl.h"

template <typename T>
class StackTest : public testing::Test
{
protected:
    using MyType = T;
    puza::Stack<T> stk_[2];
    T val1_ = static_cast<T>(0);
    T val2_ = static_cast<T>(1);
    const size_t MAX_ITER = 1000000;
};

typedef testing::Types<double, float, int, short, char, bool> MyTypes;

TYPED_TEST_SUITE(StackTest, MyTypes);

TYPED_TEST(StackTest, push_top)
{
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
        EXPECT_TRUE(this->stk_[0].top() == this->val2_);
    }
}

TYPED_TEST(StackTest, push_pop)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
        T test_value1 = this->stk_[0].top();
        this->stk_[0].pop();
        T test_value2 = this->stk_[0].top();
        EXPECT_TRUE((this->val2_ == test_value1) && (this->val1_ == test_value2));
    }
}

TYPED_TEST(StackTest, start_size)
{
    EXPECT_TRUE(this->stk_[0].size() == 0);
}

TYPED_TEST(StackTest, empty)
{
    EXPECT_TRUE(this->stk_[0].empty());
}

TYPED_TEST(StackTest, push_size)
{
    EXPECT_TRUE(this->stk_[0].size() == 0);
    for (size_t i = 1; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        EXPECT_TRUE(this->stk_[0].size() == i);
    }
}

TYPED_TEST(StackTest, pop_size)
{
    for (size_t i = 1; i <= this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
    }
    EXPECT_TRUE(this->stk_[0].size() == this->MAX_ITER);

    for (size_t i = this->MAX_ITER; i > 0; i--)
    {
        EXPECT_TRUE(this->stk_[0].size() == i);
        this->stk_[0].pop();
    }
}

TYPED_TEST(StackTest, clear)
{
    for (size_t i = 1; i <= this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
    }
    EXPECT_TRUE(this->stk_[0].size() == this->MAX_ITER);
    this->stk_[0].clear();
    EXPECT_TRUE(this->stk_[0].size() == 0);

    for (size_t i = 1; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
        EXPECT_TRUE(this->stk_[0].size() == i + 1);
        EXPECT_TRUE(this->stk_[0].top() == this->val2_);
        this->stk_[0].pop();
    }
}

TYPED_TEST(StackTest, operator_equal)
{
    EXPECT_TRUE(this->stk_[0] == this->stk_[1]);
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);

        this->stk_[1].push(this->val1_);
        this->stk_[1].push(this->val2_);
    }
    EXPECT_TRUE(this->stk_[0] == this->stk_[1]);
    
    this->stk_[0].clear();
    this->stk_[1].clear();
    this->stk_[0].push(this->val1_);
    this->stk_[1].push(this->val2_);
    EXPECT_FALSE(this->stk_[0] == this->stk_[1]);
}

TYPED_TEST(StackTest, operator_not_equal)
{
    EXPECT_FALSE(this->stk_[0] != this->stk_[1]);
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);

        this->stk_[1].push(this->val1_);
        this->stk_[1].push(this->val2_);
    }
    EXPECT_FALSE(this->stk_[0] != this->stk_[1]);
    
    this->stk_[0].clear();
    this->stk_[1].clear();
    this->stk_[0].push(this->val1_);
    this->stk_[1].push(this->val2_);
    EXPECT_TRUE(this->stk_[0] != this->stk_[1]);
}

TYPED_TEST(StackTest, assignment)
{
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
    }
    this->stk_[1] = this->stk_[0];
    EXPECT_TRUE(this->stk_[0] == this->stk_[1]);
}

TYPED_TEST(StackTest, copy_constructor)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
    }
    puza::Stack<T>stk(this->stk_[0]);
    EXPECT_TRUE(this->stk_[0] == stk);
}

TYPED_TEST(StackTest, swap)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER; i++)
    {
        this->stk_[0].push(this->val1_);
        this->stk_[0].push(this->val2_);
        this->stk_[1].push(this->val2_);
        this->stk_[1].push(this->val1_);
    }
    puza::Stack<T>stk0(this->stk_[0]);
    puza::Stack<T>stk1(this->stk_[1]);
    this->stk_[0].swap(&this->stk_[1]);
    EXPECT_TRUE((this->stk_[1] == stk0) && (this->stk_[0] == stk1));
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}