#include "HashTable/HashTable-impl.h"

#include <gtest/gtest.h>

constexpr size_t MAX_ITER = 1000000;
using MyHT = puza::HashTable<std::string, size_t>;

TEST(HashTableTest, DefaultCtor)
{
    MyHT ht;
    EXPECT_TRUE(ht.capacity() == ht.DEFAULT_CAPACITY_);
}

TEST(HashTableTest, CapacityCtor)
{
    MyHT ht(100);
    EXPECT_TRUE(ht.capacity() == 100);
}

TEST(HashTableTest, CopyCtor)
{
    MyHT ht1;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
    }

    MyHT ht2(ht1);
    EXPECT_TRUE(ht2.size() == ht1.size());
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht1[std::to_string(i)] == ht2[std::to_string(i)]);
        EXPECT_TRUE(ht2[std::to_string(i)] == 2 * i);
    }
}

TEST(HashTableTest, MoveCtor)
{
    MyHT ht1;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
    }

    MyHT ht2(std::move(ht1));
    EXPECT_TRUE(ht2.size() == MAX_ITER);
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht2[std::to_string(i)] == 2 * i);
    }
}

TEST(HashTableTest, CopyOp)
{
    MyHT ht1;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
    }

    MyHT ht2;
    ht2 = ht1;
    EXPECT_TRUE(ht2.size() == ht1.size());
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht1[std::to_string(i)] == ht2[std::to_string(i)]);
        EXPECT_TRUE(ht2[std::to_string(i)] == 2 * i);
    }
}

TEST(HashTableTest, MoveOp)
{
    MyHT ht1;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
    }

    MyHT ht2;
    ht2 = std::move(ht1);
    EXPECT_TRUE(ht2.size() == MAX_ITER);
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht2[std::to_string(i)] == 2 * i);
    }
}

TEST(HashTableTest, EqualOp)
{
    MyHT ht1;
    MyHT ht2;
    EXPECT_TRUE(ht1 == ht2);
    for (size_t i = 0; i < 10; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
        EXPECT_FALSE(ht1 == ht2);
        ht2.insert(std::to_string(i), 2 * i);
        EXPECT_TRUE(ht1 == ht2);
    }
}

TEST(HashTableTest, NotEqualOp)
{
    MyHT ht1;
    MyHT ht2;
    EXPECT_FALSE(ht1 != ht2);
    for (size_t i = 0; i < 10; i++)
    {
        ht1.insert(std::to_string(i), 2 * i);
        EXPECT_TRUE(ht1 != ht2);
        ht2.insert(std::to_string(i), 2 * i);
        EXPECT_FALSE(ht1 != ht2);
    }
}

TEST(HashTableTest, Empty)
{
    MyHT ht;
    EXPECT_TRUE(ht.empty());
    ht.insert(std::to_string(1), 1);
    EXPECT_FALSE(ht.empty());
}

TEST(HashTableTest, Size)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht.size() == i);
        ht.insert(std::to_string(i), 2 * i);
    }
}

TEST(HashTableTest, Clear)
{
    MyHT ht;
    ht.clear();
    EXPECT_TRUE(ht.size() == 0);

    for (size_t i = 0; i < MAX_ITER; i++)
    {
         ht.insert(std::to_string(i), 2 * i);
    }
    EXPECT_TRUE(ht.size() == MAX_ITER);  

    ht.clear();
    EXPECT_TRUE(ht.size() == 0);
}

TEST(HashTableTest, Insert)
{
    MyHT ht;
    for (size_t i = 1; i < MAX_ITER; i++)
    {
        ht.insert(std::to_string(i), 2 * i);
        EXPECT_TRUE(ht[std::to_string(i)] == 2 * i);

        EXPECT_TRUE(ht.size() == i);

        ht.insert(std::to_string(i), 4 * i);
        EXPECT_TRUE(ht[std::to_string(i)] == 2 * i);

        EXPECT_TRUE(ht.size() == i);
    }
}

TEST(HashTableTest, InsertOrAssign)
{
    MyHT ht;
    for (size_t i = 1; i < MAX_ITER; i++)
    {
        ht.insert_or_assign(std::to_string(i), 2 * i);
        EXPECT_TRUE(ht[std::to_string(i)] == 2 * i);

        EXPECT_TRUE(ht.size() == i);

        ht.insert_or_assign(std::to_string(i), 4 * i);
        EXPECT_TRUE(ht[std::to_string(i)] == 4 * i);

        EXPECT_TRUE(ht.size() == i);
    }
}

TEST(HashTableTest, AccesOperator)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht.size() == i);
        EXPECT_FALSE(ht.contains(std::to_string(i)));

        ht[std::to_string(i)];
        EXPECT_TRUE(ht.contains(std::to_string(i)));
        EXPECT_TRUE(ht[std::to_string(i)] == 0);

        ht[std::to_string(i)] = 5 * i;
        EXPECT_TRUE(ht[std::to_string(i)] == 5 * i);
    }
}

TEST(HashTableTest, Find)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht.insert(std::to_string(i), 2 * i);
    }

    for (size_t i = 1; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht.find(std::to_string(i)) != nullptr);
        EXPECT_TRUE(ht.find(std::to_string(-i)) == nullptr);
        EXPECT_TRUE(*ht.find(std::to_string(i)) == 2 * i);
    }
}

TEST(HashTableTest, Contains)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht.insert(std::to_string(i), 2 * i);
    }

    for (size_t i = 1; i < MAX_ITER; i++)
    {
        EXPECT_TRUE(ht.contains(std::to_string(i)));
        EXPECT_FALSE(ht.contains(std::to_string(-i)));
    }
}

TEST(HashTableTest, Iterator)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht.insert(std::to_string(i), 2 * i);
    }

    size_t num = 0;
    for (auto& it : ht)
    {
        EXPECT_TRUE(it.value == 2 * num);
        it.value = 0;
        EXPECT_TRUE(it.value == 0);
        num++;
    }
}

TEST(HashTableTest, ConstIterator)
{
    MyHT ht;
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        ht.insert(std::to_string(i), 2 * i);
    }

    size_t num = 0;
    for (const auto& it : ht)
    {
        EXPECT_TRUE(it.value == 2 * num);
        num++;
    }
}