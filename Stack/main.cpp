/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses c++ stack                                      *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright � 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include "Stack.h"

int main()
{
    Stack<double> stk;

    stk.Push(10.1);
    stk.Push(-12.2);
    stk.Pop();
    stk.Push(11.22552e-2);
    stk.Push(-0.4);

    Stack<double> stk2(stk);
    stk2.Pop();
    stk2.Pop();
    stk2.Pop();
    printf("%lf\n", stk2.Pop());

    return 0;
}

