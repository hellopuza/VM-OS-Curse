/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses stack                                          *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Stack.h"
#include <iostream>

template <typename TYPE>
void test_push_top (TYPE value1, TYPE value2)
{
    Stack<TYPE> stk;
    stk.push(value1);
    stk.push(value2);
    printf("test push-top \t\t\t%s\n", value2 == stk.top() ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_push_pop (TYPE value1, TYPE value2)
{
    Stack<TYPE> stk;
    stk.push(value1);
    stk.push(value2);

    TYPE test_value1 = stk.top();
    stk.pop();
    TYPE test_value2 = stk.top();
    printf("test push-pop \t\t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_start_size (TYPE value)
{
    Stack<TYPE> stk;
    bool test = (stk.size() == 0);
    printf("test start-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_push_size (TYPE value)
{
    Stack<TYPE> stk;
    bool test = (stk.size() == 0);

    stk.push(value);
    test = test && (stk.size() == 1);
    stk.push(value);
    test = test && (stk.size() == 2);

    printf("test push-size \t\t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_pop_size (TYPE value)
{
    Stack<TYPE> stk;
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

template <typename TYPE>
void test_clean_size (TYPE value)
{
    Stack<TYPE> stk;
    stk.push(value);
    stk.push(value);
    stk.clean();
    printf("test clean-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_after_clean (TYPE value1, TYPE value2)
{
    Stack<TYPE> stk;
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

template <typename TYPE>
void test_big_size (TYPE value1, TYPE value2, TYPE value3)
{
    Stack<TYPE> stk;
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

template <typename TYPE>
void test_assignment (TYPE value1, TYPE value2)
{
    Stack<TYPE> stk1;
    stk1.push(value1);
    stk1.push(value2);
    Stack<TYPE> stk2;
    stk2 = stk1;

    TYPE test_value1 = stk2.top();
    stk2.pop();
    TYPE test_value2 = stk2.top();
    printf("test assignment \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

template <typename TYPE>
void test_copy_constructor (TYPE value1, TYPE value2)
{
    Stack<TYPE> stk1;
    stk1.push(value1);
    stk1.push(value2);
    Stack<TYPE> stk2(stk1);

    TYPE test_value1 = stk2.top();
    stk2.pop();
    TYPE test_value2 = stk2.top();
    printf("test copy-constructor \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

int main()
{
    test_push_top(1, 2);
    test_push_top(0.0, -3.0);

    test_push_pop(1u, 2u);
    test_push_pop(1.0f, -3.0f);

    test_start_size(1);
    test_start_size(2.0);

    test_push_size(1);
    test_push_size(2.0);

    test_pop_size(1u);
    test_pop_size(2l);

    test_clean_size(1);
    test_clean_size(-1.0);

    test_after_clean(1u, 2u);
    test_after_clean(2, -3);

    test_big_size(1, -2, 3);
    test_big_size(1.0, 2.0, -3.0);

    test_assignment(1.0f, -2.0f);
    test_assignment(-1, 0);

    test_copy_constructor(1, -2);
    test_copy_constructor(1.0f, -3.0f);

    return 0;
}

