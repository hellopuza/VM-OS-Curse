/*------------------------------------------------------------------------------
    * File:        main.cpp                                                    *
    * Description: Program uses complex numbers                                *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include "Complex.h"
#include <complex>
#include <iostream>

bool isNIL (double num)
{
    return (abs(num) < 1e-7);
}

#define INIT_TEST \
        std::complex<double> std_c1; \
        std::complex<double> std_c2; \
        Complex my_res; \
        std::complex<double> std_res;

#define TEST(c1, c2, op) \
        std_c1 = {c1.re, c1.im}; \
        std_c2 = {c2.re, c2.im}; \
        my_res = c1 op c2; \
        std_res = std_c1 op std_c2; \
        printf("TEST( (%.5lf, %.5lf) " #op " (%.5lf, %.5lf) = (%.5lf, %.5lf) || (%.5lf, %.5lf)\t%s\n", \
               c1.re, c1.im, c2.re, c2.im, my_res.re, my_res.im, real(std_res), imag(std_res), \
               (isNIL(my_res.re - real(std_res)) && isNIL(my_res.im - imag(std_res))) ? "SUCCESSFUL" : "FAILED");

int main()
{
    INIT_TEST;

    TEST(Complex(1, 2), Complex(1, 2), +);
    TEST(Complex(1, 2), Complex(1, 2), -);
    TEST(Complex(0, 0), Complex(1, 2), /);
    TEST(Complex(0, 1), Complex(1, 2), *);
    TEST(Complex(0, 0), Complex(0, 2), /);
    TEST(Complex(0, 2), Complex(8, 9), -);
    TEST(Complex(1, 1), Complex(1, 0), /);
    TEST(Complex(0, 1), Complex(1, 2), *);
    TEST(Complex(2, 2), Complex(9, 2), *);
    TEST(Complex(6, 2), Complex(0, 2), /);
    TEST(Complex(0, 2), Complex(0, 2), +);
    TEST(Complex(1, 0), Complex(1, 0), +);

    return 0;
}
