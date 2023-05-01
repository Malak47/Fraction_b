//
// Created by malaklinux on 4/16/23.
//

#ifndef FRACTION_A_FRACTION_HPP
#define FRACTION_A_FRACTION_HPP

#include <iostream>
#include <stdexcept>
using namespace std;
namespace ariel {
    class Fraction {
    private:
        int numerator;
        int denominator;

        int gcd(int num1, int num2);

        void reduce();

        Fraction fromFloat(float num);

    public:

        Fraction(int numerator, int denominator);

        Fraction(float num);

        Fraction();

        int getNumerator() const;

        void setNumerator(int numerator);

        int getDenominator() const;

        void setDenominator(int denominator);

        friend Fraction operator+(const Fraction &frac1, const Fraction &frac2);

        friend Fraction operator-(const Fraction &frac1, const Fraction &frac2);

        friend Fraction operator*(const Fraction &frac1, const Fraction &frac2);

        friend Fraction operator/(const Fraction &frac1, const Fraction &frac2);

        friend bool operator==(const Fraction &frac1, const Fraction &frac2);

        friend bool operator!=(const Fraction &frac1, const Fraction &frac2);

        friend bool operator>(const Fraction &frac1, const Fraction &frac2);

        friend bool operator<(const Fraction &frac1, const Fraction &frac2);

        friend bool operator>=(const Fraction &frac1, const Fraction &frac2);

        friend bool operator<=(const Fraction &frac1, const Fraction &frac2);

        Fraction &operator++();

        Fraction operator++(int);

        Fraction &operator--();

        Fraction operator--(int);

        friend ostream &operator<<(ostream &ostream, const Fraction &frac);

        friend istream &operator>>(istream &istream, Fraction &frac);
    };
}
#endif //FRACTION_A_FRACTION_HPP

