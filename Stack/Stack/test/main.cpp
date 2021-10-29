#include "Stack/Stack-impl.h"

#include <gtest/gtest.h>

template<typename T>
class StackTest : public testing::Test
{
protected:
    using MyType = T;
    puza::Stack<T> stk_[2];
    T val1_ = static_cast<T> (0);
    T val2_ = static_cast<T> (1);
    const size_t MAX_ITER_ = 1000000;
};

typedef testing::Types<double, float, int, char, bool> MyTypes;

TYPED_TEST_SUITE (StackTest, MyTypes, );

TYPED_TEST (StackTest, PushTop)
{
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
        EXPECT_TRUE (this->stk_[0].top () == this->val2_);
    }
}

TYPED_TEST (StackTest, PushPop)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
        T test_value1 = this->stk_[0].top ();
        this->stk_[0].pop ();
        T test_value2 = this->stk_[0].top ();
        EXPECT_TRUE ((this->val2_ == test_value1) && (this->val1_ == test_value2));
    }
}

TYPED_TEST (StackTest, StartSize)
{
    EXPECT_TRUE (this->stk_[0].empty ());
}

TYPED_TEST (StackTest, PushSize)
{
    for (size_t i = 1; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        EXPECT_TRUE (this->stk_[0].size () == i);
    }
}

TYPED_TEST (StackTest, PopSize)
{
    for (size_t i = 1; i <= this->MAX_ITER_; i++) { this->stk_[0].push (this->val1_); }
    EXPECT_TRUE (this->stk_[0].size () == this->MAX_ITER_);

    for (size_t i = this->MAX_ITER_; i > 0; i--)
    {
        EXPECT_TRUE (this->stk_[0].size () == i);
        this->stk_[0].pop ();
    }
}

TYPED_TEST (StackTest, Clear)
{
    for (size_t i = 1; i <= this->MAX_ITER_; i++) { this->stk_[0].push (this->val1_); }
    EXPECT_TRUE (this->stk_[0].size () == this->MAX_ITER_);
    this->stk_[0].clear ();
    EXPECT_TRUE (this->stk_[0].empty ());

    for (size_t i = 1; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
        EXPECT_TRUE (this->stk_[0].size () == i + 1);
        EXPECT_TRUE (this->stk_[0].top () == this->val2_);
        this->stk_[0].pop ();
    }
}

TYPED_TEST (StackTest, OperatorEqual)
{
    EXPECT_TRUE (this->stk_[0] == this->stk_[1]);
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);

        this->stk_[1].push (this->val1_);
        this->stk_[1].push (this->val2_);
    }
    EXPECT_TRUE (this->stk_[0] == this->stk_[1]);

    this->stk_[0].clear ();
    this->stk_[1].clear ();
    this->stk_[0].push (this->val1_);
    this->stk_[1].push (this->val2_);
    EXPECT_FALSE (this->stk_[0] == this->stk_[1]);
}

TYPED_TEST (StackTest, OperatorNotEqual)
{
    EXPECT_FALSE (this->stk_[0] != this->stk_[1]);
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);

        this->stk_[1].push (this->val1_);
        this->stk_[1].push (this->val2_);
    }
    EXPECT_FALSE (this->stk_[0] != this->stk_[1]);

    this->stk_[0].clear ();
    this->stk_[1].clear ();
    this->stk_[0].push (this->val1_);
    this->stk_[1].push (this->val2_);
    EXPECT_TRUE (this->stk_[0] != this->stk_[1]);
}

TYPED_TEST (StackTest, Assignment)
{
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
    }
    this->stk_[1] = this->stk_[0];
    EXPECT_TRUE (this->stk_[0] == this->stk_[1]);
}

TYPED_TEST (StackTest, CopyConstructor)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
    }
    puza::Stack<T> stk (this->stk_[0]);
    EXPECT_TRUE (this->stk_[0] == stk);
}

TYPED_TEST (StackTest, Swap)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->stk_[0].push (this->val1_);
        this->stk_[0].push (this->val2_);
        this->stk_[1].push (this->val2_);
        this->stk_[1].push (this->val1_);
    }
    puza::Stack<T> stk0 (this->stk_[0]);
    puza::Stack<T> stk1 (this->stk_[1]);
    this->stk_[0].swap (&this->stk_[1]);
    EXPECT_TRUE ((this->stk_[1] == stk0) && (this->stk_[0] == stk1));
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}