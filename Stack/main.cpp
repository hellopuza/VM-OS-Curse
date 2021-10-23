#include <iostream>
#include <typeinfo>
#include "Stack/Stack-impl.h"

#define STATUS(cond) ((cond) ? "SUCCESSFUL" : "FAILED")

template <typename T>
void test_push_top (T value1, T value2)
{
    puza::Stack<T> stk;
    stk.push(value1);
    stk.push(value2);
    std::cout << "test " << typeid(T).name() << " push-top \t\t";
    std::cout << STATUS(value2 == stk.top()) << "\n";
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
    std::cout << "test " << typeid(T).name() << " push-pop \t\t";
    std::cout << STATUS((value2 == test_value1) && (value1 == test_value2)) << "\n";
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

    std::cout << "test " << typeid(T).name() << " operator-equal \t\t";
    std::cout << STATUS((stk1 == stk2) && !(stk3 == stk4)) << "\n";
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

    std::cout << "test " << typeid(T).name() << " operator-not-equal \t";
    std::cout << STATUS((stk1 != stk2) && (stk3 != stk4)) << "\n";
}

template <typename T>
void test_start_size (T value)
{
    puza::Stack<T>stk;
    std::cout << "test " << typeid(T).name() << " start-size \t\t";
    std::cout << STATUS(stk.size() == 0) << "\n";
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

    std::cout << "test " << typeid(T).name() << " push-size \t\t";
    std::cout << STATUS(test) << "\n";
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

    std::cout << "test " << typeid(T).name() << " pop-size \t\t";
    std::cout << STATUS(test) << "\n";
}

template <typename T>
void test_clear_size (T value)
{
    puza::Stack<T>stk;
    stk.push(value);
    stk.push(value);
    stk.clear();
    std::cout << "test " << typeid(T).name() << " clear-size \t\t";
    std::cout << STATUS(stk.size() == 0) << "\n";
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
    std::cout << "test " << typeid(T).name() << " after-clear \t\t";
    std::cout << STATUS(test) << "\n";
}

template <typename T>
void test_big_size (T value1, T value2, T value3)
{
    puza::Stack<T>stk;
    size_t test_size = 0;
    bool test = true;
    for (size_t i = 0; i < 1000000; i++)
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
    std::cout << "test " << typeid(T).name() << " big-size \t\t";
    std::cout << STATUS(test && (test_size == stk.size())) << "\n";
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
    std::cout << "test " << typeid(T).name() << " assignment \t\t";
    std::cout << STATUS((value2 == test_value1) && (value1 == test_value2)) << "\n";
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
    std::cout << "test " << typeid(T).name() << " copy-constructor \t";
    std::cout << STATUS((value2 == test_value1) && (value1 == test_value2)) << "\n";
}

int main()
{
    test_push_top(true, false);
    test_push_pop(true, false);
    test_operator_equal(false, true);
    test_operator_not_equal(true, false);
    test_start_size(true);
    test_push_size(false);
    test_pop_size(true);
    test_clear_size(true);
    test_after_clear(true, false);
    test_big_size(true, false, true);
    test_assignment(false, true);
    test_copy_constructor(true, false);

    return 0;
}
