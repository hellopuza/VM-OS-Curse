#include "Queue/Queue-impl.h"

#include <gtest/gtest.h>

template<typename T>
class QueueTest : public testing::Test
{
protected:
    using MyType = T;
    puza::Queue<T> queue_[2];
    T val1_ = static_cast<T>(0);
    T val2_ = static_cast<T>(1);
    const size_t MAX_ITER_ = 1000000;
};

typedef testing::Types<double, float, int, char, bool> MyTypes;

TYPED_TEST_SUITE(QueueTest, MyTypes, );

TYPED_TEST(QueueTest, PushFrontBack)
{
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[0].push(this->val2_);
        EXPECT_TRUE(this->queue_[0].front() != this->queue_[0].back());
    }
}

TYPED_TEST(QueueTest, PopFrontBack)
{
    this->queue_[0].push(this->val1_);
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val2_);
        EXPECT_TRUE(this->queue_[0].front() != this->queue_[0].back());
        this->queue_[0].pop();
        EXPECT_TRUE(this->queue_[0].front() == this->queue_[0].back());
        this->queue_[0].pop();
        this->queue_[0].push(this->val1_);
    }
}

TYPED_TEST(QueueTest, StartSize)
{
    EXPECT_TRUE(this->queue_[0].empty());
}

TYPED_TEST(QueueTest, PushSize)
{
    for (size_t i = 1; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        EXPECT_TRUE(this->queue_[0].size() == i);
    }
}

TYPED_TEST(QueueTest, PopSize)
{
    for (size_t i = 1; i <= this->MAX_ITER_; i++) { this->queue_[0].push(this->val1_); }
    EXPECT_TRUE(this->queue_[0].size() == this->MAX_ITER_);

    for (size_t i = this->MAX_ITER_; i > 0; i--)
    {
        EXPECT_TRUE(this->queue_[0].size() == i);
        this->queue_[0].pop();
    }
}

TYPED_TEST(QueueTest, OperatorEqual)
{
    EXPECT_TRUE(this->queue_[0] == this->queue_[1]);

    this->queue_[0].push(this->val1_);
    this->queue_[1].push(this->val2_);
    EXPECT_FALSE(this->queue_[0] == this->queue_[1]);
    this->queue_[0].pop();
    this->queue_[1].pop();

    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[1].push(this->val2_);
    }
    EXPECT_FALSE(this->queue_[0] == this->queue_[1]);
}

TYPED_TEST(QueueTest, OperatorNotEqual)
{
    EXPECT_FALSE(this->queue_[0] != this->queue_[1]);

    this->queue_[0].push(this->val1_);
    this->queue_[1].push(this->val2_);
    EXPECT_TRUE(this->queue_[0] != this->queue_[1]);
    this->queue_[0].pop();
    this->queue_[1].pop();

    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[1].push(this->val2_);
    }
    EXPECT_TRUE(this->queue_[0] != this->queue_[1]);
}

TYPED_TEST(QueueTest, Assignment)
{
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[0].push(this->val2_);
    }
    this->queue_[1] = this->queue_[0];
    EXPECT_TRUE(this->queue_[0] == this->queue_[1]);
}

TYPED_TEST(QueueTest, CopyConstructor)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[0].push(this->val2_);
    }
    puza::Queue<T> queue(this->queue_[0]);
    EXPECT_TRUE(this->queue_[0] == queue);
}

TYPED_TEST(QueueTest, Swap)
{
    using T = typename TestFixture::MyType;
    for (size_t i = 0; i < this->MAX_ITER_; i++)
    {
        this->queue_[0].push(this->val1_);
        this->queue_[0].push(this->val2_);
        this->queue_[1].push(this->val2_);
        this->queue_[1].push(this->val1_);
    }
    puza::Queue<T> queue0(this->queue_[0]);
    puza::Queue<T> queue1(this->queue_[1]);
    this->queue_[0].swap(&this->queue_[1]);
    EXPECT_TRUE((this->queue_[1] == queue0) && (this->queue_[0] == queue1));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}