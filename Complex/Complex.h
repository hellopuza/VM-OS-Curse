/*------------------------------------------------------------------------------
    * File:        Complex.h                                                   *
    * Description: Complex numbers library.                                    *
    * Created:     24 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright © 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <iostream>
#include <math.h>

struct Complex
{
    double re = NAN;
    double im = NAN;

    Complex () {}

    Complex (double real, double imag):
        re(real),
        im(imag)
    {}

    ~Complex ()
    {
        re = NAN;
        im = NAN;
    }
    
    Complex (const Complex& obj) :
        re(obj.re),
        im(obj.im)
    {}

    Complex& operator = (const Complex& obj)
    {
        re = obj.re;
        im = obj.im;

        return *this;
    }

    bool operator == (const Complex& obj) const
    {
        return (re == obj.re) && (im == obj.im);
    }

    Complex operator + (float k) const
    {
        return Complex
        (
            re + k,
            im
        );
    }

    Complex operator - (float k) const
    {
        return Complex
        (
            re - k,
            im
        );
    }

    Complex operator + (const Complex& c) const
    {
        return Complex
        (
            re + c.re,
            im + c.im
        );
    }

    Complex operator - (const Complex& c) const
    {
        return Complex
        (
            re - c.re,
            im - c.im
        );
    }

    Complex operator * (float k) const
    {
        return Complex
        (
            re * k,
            im * k
        );
    }

    Complex operator / (float k) const
    {
        return Complex
        (
            re / k,
            im / k
        );
    }

    Complex operator * (const Complex& c) const
    {
        return Complex
        (
            re * c.re - im * c.im,
            re * c.im + im * c.re
        );
    }

    Complex operator / (const Complex& c) const
    {
        return Complex
        (
            (re * c.re + im * c.im) / (c.re * c.re + c.im * c.im),
            (im * c.re - re * c.im) / (c.re * c.re + c.im * c.im)
        );
    }

    Complex& operator += (const Complex& c)
    {
        *this = *this + c;
        return *this;
    }

    Complex& operator -= (const Complex& c)
    {
        *this = *this - c;
        return *this;
    }

    Complex& operator *= (float k)
    {
        *this = *this * k;
        return *this;
    }

    Complex& operator /= (float k)
    {
        *this = *this / k;
        return *this;
    }

    Complex& operator *= (const Complex& c)
    {
        *this = *this * c;
        return *this;
    }

    Complex& operator /= (const Complex& c)
    {
        *this = *this / c;
        return *this;
    }

    Complex operator - ()
    {
        return Complex(-re, -im);
    }
};

#endif // COMPLEX_H_INCLUDED
