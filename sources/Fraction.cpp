//
// Created by malaklinux on 4/16/23.
//

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
        Fraction::check_overflow(frac1, frac2, '+');
        int numerator = frac1.numerator * frac2.denominator + frac1.denominator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator-(const Fraction &frac1, const Fraction &frac2) {
        Fraction::check_overflow(frac1, frac2, '-');
        int numerator = frac1.numerator * frac2.denominator - frac1.denominator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator*(const Fraction &frac1, const Fraction &frac2) {
        Fraction::check_overflow(frac1, frac2, '*');
        int numerator = frac1.numerator * frac2.numerator;
        int denominator = frac1.denominator * frac2.denominator;
        return {numerator, denominator};
    }

    Fraction operator/(const Fraction &frac1, const Fraction &frac2) {
        if (frac2 == 0) throw runtime_error("Division by zero.");
        Fraction::check_overflow(frac1, frac2, '/');
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
        return (double) frac1.numerator / (double) frac1.denominator >
               (double) frac2.numerator / (double) frac2.denominator;
    }

    bool operator<(const Fraction &frac1, const Fraction &frac2) {
        return (double) frac1.numerator / (double) frac1.denominator <
               (double) frac2.numerator / (double) frac2.denominator;
    }

    bool operator>=(const Fraction &frac1, const Fraction &frac2) {
        return !(frac1 < frac2);
    }

    bool operator<=(const Fraction &frac1, const Fraction &frac2) {
        return !(frac1 > frac2);
    }

    Fraction &Fraction::operator++() {
        numerator += denominator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        reduce();
        return temp;
    }

    Fraction &Fraction::operator--() {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        reduce();
        return temp;
    }

    ostream &operator<<(ostream &os, const Fraction &frac) {
        int numerator = frac.numerator;
        int denominator = frac.denominator;
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        os << numerator << "/" << denominator;
        return os;
    }

    istream &operator>>(istream &is, Fraction &frac) {
        is >> frac.numerator >> frac.denominator;

        if (is.fail()) {
            throw runtime_error("Invalid fraction format.");
        }
        if (frac.denominator == 0) {
            throw runtime_error("Denominator cannot be zero.");
        }
        if (frac.denominator < 0) {
            frac.numerator *= -1;
            frac.denominator *= -1;
        }
        frac.reduce();

        return is;
    }

    void Fraction::check_overflow(const Fraction &frac1, const Fraction &frac2, char optr) {
        auto max = std::numeric_limits<int>::max;
        auto min = std::numeric_limits<int>::min;
        int64_t result1 = static_cast<int64_t>(frac1.numerator) * static_cast<int64_t>(frac2.denominator);
        int64_t result2 = static_cast<int64_t>(frac1.denominator) * static_cast<int64_t>(frac2.numerator);

        switch (optr) {
            case '+':
                if (result1 > max() || result1 < min() ||
                    result2 > max() || result2 < min() ||
                    (result1 + result2) > max() ||
                    (result1 + result2) < min()) {
                    throw overflow_error("Overflow in addition operation.");
                }
                break;
            case '-':
                if (result1 > max() || result1 < min() ||
                    result2 > max() || result2 < min() ||
                    (result1 - result2) > max() ||
                    (result1 - result2) < min()) {
                    throw overflow_error("Overflow in subtraction operation.");
                }
                break;
            case '*':
                if (result1 > max() || result1 < min() ||
                    result2 > max() || result2 < min()) {
                    throw overflow_error("Overflow in multiplication operation.");
                }
                break;
            case '/':
                if (result1 > max() || result1 < min() ||
                    result2 > max() || result2 < min()) {
                    throw overflow_error("Overflow in division operation.");
                }
                break;
            default:
                break;
        }
    }
}