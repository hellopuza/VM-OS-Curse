/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses stack                                          *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * MIT License                                                              *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Stack.h"
#include <iostream>

void test_push_top (int value1, int value2)
{
    puza::Stack stk;
    stk.push(value1);
    stk.push(value2);
    printf("test push-top \t\t\t%s\n", value2 == stk.top() ? "SUCCESSFUL" : "FAILED");
}

void test_push_pop (int value1, int value2)
{
    puza::Stack stk;
    stk.push(value1);
    stk.push(value2);

    int test_value1 = stk.top();
    stk.pop();
    int test_value2 = stk.top();
    printf("test push-pop \t\t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

void test_operator_equal (int value1, int value2)
{
    puza::Stack stk1;
    stk1.push(value1);
    stk1.push(value2);

    puza::Stack stk2;
    stk2.push(value1);
    stk2.push(value2);

    puza::Stack stk3;
    stk3.push(value1);

    puza::Stack stk4;
    stk4.push(value1);
    stk4.push(value2);

    printf("test operator-equal \t\t%s\n", (stk1 == stk2) && !(stk3 == stk4) ? "SUCCESSFUL" : "FAILED");
}

void test_operator_not_equal (int value1, int value2)
{
    puza::Stack stk1;
    stk1.push(value1);
    stk1.push(value1);

    puza::Stack stk2;
    stk2.push(value1);
    stk2.push(value2);

    puza::Stack stk3;
    stk3.push(value2);

    puza::Stack stk4;
    stk4.push(value1);
    stk4.push(value2);

    printf("test operator-not-equal \t%s\n", (stk1 != stk2) && (stk3 != stk4) ? "SUCCESSFUL" : "FAILED");
}

void test_start_size ()
{
    puza::Stack stk;
    bool test = (stk.size() == 0);
    printf("test start-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

void test_push_size (int value)
{
    puza::Stack stk;
    bool test = (stk.size() == 0);

    stk.push(value);
    test = test && (stk.size() == 1);
    stk.push(value);
    test = test && (stk.size() == 2);

    printf("test push-size \t\t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

void test_pop_size (int value)
{
    puza::Stack stk;
    bool test = (stk.size() == 0);

    stk.push(value);
    stk.push(value);
    test = test && (stk.size() == 2);
    stk.pop();
    test = test && (stk.size() == 1);
    stk.pop();
    test = test && (stk.size() == 0);

    printf("test pop-size \t\t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

void test_clean_size (int value)
{
    puza::Stack stk;
    stk.push(value);
    stk.push(value);
    stk.clean();
    printf("test clean-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

void test_after_clean (int value1, int value2)
{
    puza::Stack stk;
    stk.push(value1);
    stk.clean();
    stk.push(value1);
    stk.push(value2);
    bool test = (stk.size() == 2);
    test = test && (value2 == stk.top());
    stk.pop();
    test = test && (value1 == stk.top());
    test = test && (stk.size() == 1);
    printf("test after-clean \t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

void test_big_size (int value1, int value2, int value3)
{
    puza::Stack stk;
    size_t test_size = 0;
    bool test = true;
    for (int i = 0; i < 10; i++)
    {
        stk.push(value1);
        stk.push(value2);
        stk.push(value3);
        stk.push(value1);
        test = test && (value1 == stk.top());
        stk.pop();
        test = test && (value3 == stk.top());
        test_size += 3;
    }
    printf("test big-size \t\t\t%s\n", test && (test_size == stk.size()) ? "SUCCESSFUL" : "FAILED");
}

void test_assignment (int value1, int value2)
{
    puza::Stack stk1;
    stk1.push(value1);
    stk1.push(value2);
    puza::Stack stk2;
    stk2 = stk1;

    int test_value1 = stk2.top();
    stk2.pop();
    int test_value2 = stk2.top();
    printf("test assignment \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

void test_copy_constructor (int value1, int value2)
{
    puza::Stack stk1;
    stk1.push(value1);
    stk1.push(value2);
    puza::Stack stk2(stk1);

    int test_value1 = stk2.top();
    stk2.pop();
    int test_value2 = stk2.top();
    printf("test copy-constructor \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

int main()
{
    test_push_top(1, 2);
    test_push_pop(3, 4);
    test_operator_equal(1, 2);
    test_operator_not_equal(1, 2);
    test_start_size();
    test_push_size(1);
    test_pop_size(11);
    test_clean_size(1);
    test_after_clean(1, 2);
    test_big_size(1, 2, 3);
    test_assignment(1, 2);
    test_copy_constructor(1, 2);

    return 0;
}
