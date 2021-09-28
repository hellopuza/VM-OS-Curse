/*------------------------------------------------------------------------------
    * File:        Complex.cpp                                                 *
    * Description: Complex methods implementations.                            *
    * Created:     25 sep 2021                                                 *
    * Author:      Artem Puzankov                                              *
    * Email:       puzankov.ao@phystech.edu                                    *
    * GitHub:      https://github.com/hellopuza                                *
    * Copyright � 2021 Artem Puzankov. All rights reserved.                    *
    *///------------------------------------------------------------------------

#include "Complex.h"
#include <iostream>
#include <cmath>

Complex::Complex() :
    re(0.0),
    im(0.0)
{}

Complex::Complex(float real, float imag) :
    re(real),
    im(imag)
{}

Complex::~Complex()
{
    re = std::nan("");
    im = std::nan("");
}

Complex::Complex(const Complex& obj) :
    re(obj.re),
    im(obj.im)
{}

Complex& Complex::operator = (const Complex& obj)
{
    re = obj.re;
    im = obj.im;

    return *this;
}

bool Complex::operator == (const Complex& obj) const
{
    return (re == obj.re) && (im == obj.im);
}

Complex Complex::operator + (const Complex& c) const
{
    return Complex(re + c.re, im + c.im);
}

Complex Complex::operator - (const Complex& c) const
{
    return Complex(re - c.re, im - c.im);
}

Complex Complex::operator * (float k) const
{
    return Complex(re * k, im * k);
}

Complex Complex::operator / (float k) const
{
    return Complex(re / k, im / k);
}

Complex Complex::operator * (const Complex& c) const
{
    return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
}

Complex Complex::operator / (const Complex& c) const
{
    return Complex((re * c.re + im * c.im) / (c.re * c.re + c.im * c.im), (im * c.re - re * c.im) / (c.re * c.re + c.im * c.im));
}

Complex& Complex::operator += (const Complex& c)
{
    *this = Complex(re + c.re, im + c.im);
    return *this;
}

Complex& Complex::operator -= (const Complex& c)
{
    *this = Complex(re - c.re, im - c.im);
    return *this;
}

Complex& Complex::operator *= (float k)
{
    *this = Complex(re * k, im * k);
    return *this;
}

Complex& Complex::operator /= (float k)
{
    *this = Complex(re / k, im / k);
    return *this;
}

Complex& Complex::operator *= (const Complex& c)
{
    *this = Complex(re * c.re - im * c.im, re * c.im + im * c.re);
    return *this;
}

Complex& Complex::operator /= (const Complex& c)
{
    *this = Complex((re * c.re + im * c.im) / (c.re * c.re + c.im * c.im), (im * c.re - re * c.im) / (c.re * c.re + c.im * c.im));
    return *this;
}

Complex Complex::operator - () const
{
    return Complex(-re, -im);
}
