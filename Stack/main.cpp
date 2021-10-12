/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses Stack<T>                                         *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * MIT License                                                              *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Stack-impl.h"
#include <iostream>

template <typename T>
void test_push_top (T value1, T value2)
{
    puza::Stack<T> stk;
    stk.push(value1);
    stk.push(value2);
    printf("test push-top \t\t\t%s\n", value2 == stk.top() ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_push_pop (T value1, T value2)
{
    puza::Stack<T>stk;
    stk.push(value1);
    stk.push(value2);

    T test_value1 = stk.top();
    stk.pop();
    T test_value2 = stk.top();
    printf("test push-pop \t\t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_operator_equal (T value1, T value2)
{
    puza::Stack<T>stk1;
    stk1.push(value1);
    stk1.push(value2);

    puza::Stack<T>stk2;
    stk2.push(value1);
    stk2.push(value2);

    puza::Stack<T>stk3;
    stk3.push(value1);

    puza::Stack<T>stk4;
    stk4.push(value1);
    stk4.push(value2);

    printf("test operator-equal \t\t%s\n", (stk1 == stk2) && !(stk3 == stk4) ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_operator_not_equal (T value1, T value2)
{
    puza::Stack<T>stk1;
    stk1.push(value1);
    stk1.push(value1);

    puza::Stack<T>stk2;
    stk2.push(value1);
    stk2.push(value2);

    puza::Stack<T>stk3;
    stk3.push(value2);

    puza::Stack<T>stk4;
    stk4.push(value1);
    stk4.push(value2);

    printf("test operator-not-equal \t%s\n", (stk1 != stk2) && (stk3 != stk4) ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_start_size (T value)
{
    puza::Stack<T>stk;
    bool test = (stk.size() == 0);
    printf("test start-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_push_size (T value)
{
    puza::Stack<T>stk;
    bool test = (stk.size() == 0);

    stk.push(value);
    test = test && (stk.size() == 1);
    stk.push(value);
    test = test && (stk.size() == 2);

    printf("test push-size \t\t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_pop_size (T value)
{
    puza::Stack<T>stk;
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

template <typename T>
void test_clear_size (T value)
{
    puza::Stack<T>stk;
    stk.push(value);
    stk.push(value);
    stk.clear();
    printf("test clear-size \t\t%s\n", stk.size() == 0 ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_after_clear (T value1, T value2)
{
    puza::Stack<T>stk;
    stk.push(value1);
    stk.clear();
    stk.push(value1);
    stk.push(value2);
    bool test = (stk.size() == 2);
    test = test && (value2 == stk.top());
    stk.pop();
    test = test && (value1 == stk.top());
    test = test && (stk.size() == 1);
    printf("test after-clear \t\t%s\n", test ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_big_size (T value1, T value2, T value3)
{
    puza::Stack<T>stk;
    size_t test_size = 0;
    bool test = true;
    for (T i = 0; i < 10; i++)
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

template <typename T>
void test_assignment (T value1, T value2)
{
    puza::Stack<T>stk1;
    stk1.push(value1);
    stk1.push(value2);
    puza::Stack<T>stk2;
    stk2 = stk1;

    T test_value1 = stk2.top();
    stk2.pop();
    T test_value2 = stk2.top();
    printf("test assignment \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

template <typename T>
void test_copy_constructor (T value1, T value2)
{
    puza::Stack<T>stk1;
    stk1.push(value1);
    stk1.push(value2);
    puza::Stack<T>stk2(stk1);

    T test_value1 = stk2.top();
    stk2.pop();
    T test_value2 = stk2.top();
    printf("test copy-constructor \t\t%s\n", (value2 == test_value1) && (value1 == test_value2) ? "SUCCESSFUL" : "FAILED");
}

int main()
{
    test_push_top(1, 2);
    test_push_pop(3u, 4u);
    test_operator_equal(1, 2);
    test_operator_not_equal(1.0, 2.0);
    test_start_size(1);
    test_push_size(1.0f);
    test_pop_size(1);
    test_clear_size(1);
    test_after_clear(1u, 2u);
    test_big_size(1.0, 2.0, 3.0);
    test_assignment(1, 2);
    test_copy_constructor(1, 2);

    return 0;
}
