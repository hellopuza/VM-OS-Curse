/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses stack                                          *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include "Stack.h"

int main()
{
    Stack<int> stk;

    stk.push(10);
    stk.push(-12);
    stk.pop();
    stk.push(11);
    stk.push(5);

    Stack<int> stk2(stk);
    stk2.pop();
    printf("%d\n", stk2.pop());

    return 0;
}

