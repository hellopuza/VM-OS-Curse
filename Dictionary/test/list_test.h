#include "List/List-impl.h"

#include <gtest/gtest.h>

constexpr size_t MAX_ITER_ = 1000000;
using MyList = puza::List<size_t>;

TEST(ListTest, DefaultCtor)
{
    MyList list;
}

TEST(ListTest, CopyCtor)
{
    MyList list1;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list1.push_back(i);
    }

    MyList list2(list1);
    EXPECT_TRUE(list2.size() == list1.size());
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list2.front() == i);
        list2.pop_front();
    }
}

TEST(ListTest, MoveCtor)
{
    MyList list1;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list1.push_back(i);
    }

    MyList list2(std::move(list1));
    EXPECT_TRUE(list2.size() == MAX_ITER_);
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list2.front() == i);
        list2.pop_front();
    }
}

TEST(ListTest, CopyOp)
{
    MyList list1;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list1.push_back(i);
    }

    MyList list2;
    list2 = list1;
    EXPECT_TRUE(list2.size() == list1.size());
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list2.front() == i);
        list2.pop_front();
    }
}

TEST(ListTest, MoveOp)
{
    MyList list1;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list1.push_back(i);
    }

    MyList list2;
    list2 = std::move(list1);
    EXPECT_TRUE(list2.size() == MAX_ITER_);
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list2.front() == i);
        list2.pop_front();
    }
}

TEST(ListTest, EqualOp)
{
    MyList list1;
    MyList list2;
    EXPECT_TRUE(list1 == list2);
    for (size_t i = 0; i < 10; i++)
    {
        list1.push_back(i);
        EXPECT_FALSE(list1 == list2);
        list2.push_back(i);
        EXPECT_TRUE(list1 == list2);
    }
}

TEST(ListTest, NotEqualOp)
{
    MyList list1;
    MyList list2;
    EXPECT_FALSE(list1 != list2);
    for (size_t i = 0; i < 10; i++)
    {
        list1.push_back(i);
        EXPECT_TRUE(list1 != list2);
        list2.push_back(i);
        EXPECT_FALSE(list1 != list2);
    }
}

TEST(ListTest, PushFront)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list.size() == i);

        list.push_front(i);
        EXPECT_TRUE(list.front() == i);
        EXPECT_TRUE(list.back() == 0);
    }
}

TEST(ListTest, PushBack)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list.size() == i);

        list.push_back(i);
        EXPECT_TRUE(list.back() == i);
        EXPECT_TRUE(list.front() == 0);
    }
}

TEST(ListTest, PopFront)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
    }

    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list.front() == i);
        EXPECT_TRUE(list.size() == MAX_ITER_ - i);
        list.pop_front();
    }
}

TEST(ListTest, PopBack)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_front(i);
    }

    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list.back() == i);
        EXPECT_TRUE(list.size() == MAX_ITER_ - i);
        list.pop_back();
    }
}

TEST(ListTest, Front)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_front(i);
        EXPECT_TRUE(list.front() == i);
    }
}

TEST(ListTest, Back)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
        EXPECT_TRUE(list.back() == i);
    }
}

TEST(ListTest, Empty)
{
    MyList list;
    EXPECT_TRUE(list.empty());
    list.push_front(1);
    EXPECT_FALSE(list.empty());
}

TEST(ListTest, Size)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        EXPECT_TRUE(list.size() == i);
        list.push_front(i);
    }
}

TEST(ListTest, Clear)
{
    MyList list;
    list.clear();
    EXPECT_TRUE(list.size() == 0);

    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
    }
    EXPECT_TRUE(list.size() == MAX_ITER_);  

    list.clear();
    EXPECT_TRUE(list.size() == 0);
}

TEST(ListTest, Erase)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
    }

    list.erase(list.begin());
    EXPECT_TRUE(list.size() == MAX_ITER_ - 1);
    EXPECT_TRUE(list.front() == 1);

    list.erase(list.end_iter());
    EXPECT_TRUE(list.size() == MAX_ITER_ - 2);
    EXPECT_TRUE(list.back() == MAX_ITER_ - 2);
}

TEST(ListTest, Iterator)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
    }

    size_t num = 0;
    for (auto& it : list)
    {
        EXPECT_TRUE(it == num);
        it = 0;
        EXPECT_TRUE(it == 0);
        num++;
    }
}

TEST(ListTest, ConstIterator)
{
    MyList list;
    for (size_t i = 0; i < MAX_ITER_; i++)
    {
        list.push_back(i);
    }

    size_t num = 0;
    for (const auto& it : list)
    {
        EXPECT_TRUE(it == num);
        num++;
    }
}