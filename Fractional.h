#pragma once

#ifndef _CALC_FRACTIONAL_ABACKER_
#define _CALC_FRACTIONAL_ABACKER_

#define LL long long
#define EPS 1e-10

#include <cmath>
#include <algorithm>
#include "Commen.h"
#include "Algorithm.h"

using namespace std;

// LL gcd(LL a, LL b);

class Fraction {
   public:
    Fraction() : numerator(0), denominator(0) {}
    Fraction(LL numerator, LL denominator)
        : numerator(numerator), denominator(denominator) {
        yueFen();
    }
    Fraction(double val) {
        Fraction L((LL)val, 1), R((LL)val + 1, 1), Mid;
        double d;
        do {
            Mid = (L + R) / (Fraction)2;
            d = (double)Mid.numerator / Mid.denominator - val;
            if (d < 0)
                L = Mid;
            else
                R = Mid;
            L.Print();
            R.Print();
            Mid.Print();
            printf("%.15f\n", d);
        } while (d < -EPS || d > EPS);
        *this = Mid;
    }
    Fraction(int val) {
        numerator = val;
        denominator = 1;
    }
    Fraction(LL val) {
        numerator = val;
        denominator = 1;
    }

    Fraction &operator+=(const Fraction &num) {
        numerator = denominator * num.numerator + numerator * num.denominator;
        denominator *= num.denominator;
        yueFen();
        return *this;
    }
    Fraction &operator-=(const Fraction &num) {}
    Fraction &operator*=(const Fraction &num) {}
    Fraction &operator/=(const Fraction &num) {
        numerator *= num.denominator;
        denominator *= num.numerator;
        yueFen();
        return *this;
    }
    Fraction operator+(const Fraction &num) const {
        Fraction tmp = *this;
        tmp += num;

        return tmp;
    }
    Fraction operator/(const Fraction &num) const {
        Fraction tmp = *this;
        tmp /= num;

        return tmp;
    }

    void Print() const {
        printf("%" LLD "/%" LLD "\n", numerator, denominator);
    }

   private:
    LL numerator;    // fen zi
    LL denominator;  // fen mu

    void yueFen() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        LL cd = gcd(min(abs(numerator), denominator),
                    max(abs(numerator), denominator));
        numerator /= cd;
        denominator /= cd;
    }
};

#endif
