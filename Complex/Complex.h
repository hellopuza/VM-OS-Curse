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

struct Complex
{
    float re;
    float im;

    Complex ();

    Complex (float real, float imag);

    ~Complex ();
    
    Complex (const Complex& obj);

    Complex& operator = (const Complex& obj);

    bool operator == (const Complex& obj) const;

    Complex operator + (const Complex& c) const;

    Complex operator - (const Complex& c) const;

    Complex operator * (float k) const;

    Complex operator / (float k) const;

    Complex operator * (const Complex& c) const;

    Complex operator / (const Complex& c) const;

    Complex& operator += (const Complex& c);

    Complex& operator -= (const Complex& c);

    Complex& operator *= (float k);

    Complex& operator /= (float k);

    Complex& operator *= (const Complex& c);

    Complex& operator /= (const Complex& c);

    Complex operator - () const;
};

#endif // COMPLEX_H_INCLUDED
