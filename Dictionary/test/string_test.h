#include "StringUtils.h"

#include <gtest/gtest.h>

TEST(StringTest, PrepareWord)
{
    EXPECT_TRUE(puza::prepare_word("abcdes,   ") == "abcdes");
    EXPECT_TRUE(puza::prepare_word("qwer-  -") == "qwer");
    EXPECT_TRUE(puza::prepare_word("Artem,  ") == std::string());
    EXPECT_TRUE(puza::prepare_word("don't ") == std::string());
}

TEST(StringTest, LevDist)
{
    EXPECT_TRUE(puza::lev_dist("aaa", "aa") == 1);
    EXPECT_TRUE(puza::lev_dist("1234", "4321") == 4);
    EXPECT_TRUE(puza::lev_dist(" 1 ", " 2 ") == 1);
    EXPECT_TRUE(puza::lev_dist("aca", "aca") == 0);
    EXPECT_TRUE(puza::lev_dist("1234", "12") == 2);
}