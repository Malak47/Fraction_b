//
// Created by malaklinux on 4/16/23.
//

#include <cmath>
#include "Fraction.hpp"

namespace ariel {

//-------------------------------------------------------------------------------------------------------
//-----------------------  C O N S T R U C T O R S  -----------------------------------------------------
//-------------------------------------------------------------------------------------------------------

    Fraction::Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        this->numerator = numerator;
        this->denominator = denominator;
        reduce();
    }

    Fraction::Fraction(float num) {
        *this = fromFloat(num);
    }

    Fraction::Fraction() : numerator(0), denominator(1) {
    }

//-------------------------------------------------------------------------------------------------------
//-----------------------  F R A C T I O N   R E D U C E R  ---------------------------------------------
//-------------------------------------------------------------------------------------------------------

    int Fraction::gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    void Fraction::reduce() {
        int gcd_val = gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
    }

    Fraction Fraction::fromFloat(float num) {
        int denominator = pow(10, 3); // 3 digits beyond the decimal point
        int numerator = round(num * denominator);
        return {numerator, denominator};
    }

//-------------------------------------------------------------------------------------------------------
//--------------------  G E T T E R S   &   S E T T E R S  ----------------------------------------------
//-------------------------------------------------------------------------------------------------------

    int Fraction::getNumerator() const {
        return numerator;
    }

    int Fraction::getDenominator() const {
        return denominator;
    }

    void Fraction::setNumerator(int numerator) {
        Fraction::numerator = numerator;
    }

    void Fraction::setDenominator(int denominator) {
        Fraction::denominator = denominator;
    }

//-------------------------------------------------------------------------------------------------------
//-----------------------  O P E R A T O R O S ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

    Fraction operator+(const Fraction &frac1, const Fraction &frac2) {
        int numerator = frac1.numerator * frac2.denominator + frac1.denominator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator-(const Fraction &frac1, const Fraction &frac2) {
        int numerator = frac1.numerator * frac2.denominator - frac1.denominator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator*(const Fraction &frac1, const Fraction &frac2) {
        int numerator = frac1.numerator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator/(const Fraction &frac1, const Fraction &frac2) {
        if (frac2.numerator == 0) throw invalid_argument("Division by zero.");
        int numerator = frac1.numerator * frac2.denominator;
        int denominator = frac1.denominator * frac2.numerator;
        return {numerator, denominator};
    }

    bool operator==(const Fraction &frac1, const Fraction &frac2) {
        return frac1.numerator == frac2.numerator && frac1.denominator == frac2.denominator;
    }

    bool operator!=(const Fraction &frac1, const Fraction &frac2) {
        return frac1.numerator != frac2.numerator || frac1.denominator != frac2.denominator;
    }

    bool operator>(const Fraction &frac1, const Fraction &frac2) {
        return frac1.numerator * frac2.denominator > frac2.numerator * frac1.denominator;
    }

    bool operator<(const Fraction &frac1, const Fraction &frac2) {
        return frac1.numerator * frac2.denominator < frac2.numerator * frac1.denominator;
    }

    bool operator>=(const Fraction &frac1, const Fraction &frac2) {
        return !(frac1 < frac2);
    }

    bool operator<=(const Fraction &frac1, const Fraction &frac2) {
        return !(frac1 > frac2);
    }

    Fraction &Fraction::operator++() {
        numerator += denominator;
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction &Fraction::operator--() {
        numerator -= denominator;
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    ostream &operator<<(ostream &os, const Fraction &frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    istream &operator>>(istream &is, Fraction &frac) {
        char c;
        is >> frac.numerator >> c >> frac.denominator;
        if (frac.denominator == 0) throw invalid_argument("Denominator cannot be zero.");
        frac.reduce();
        return is;
    }


}