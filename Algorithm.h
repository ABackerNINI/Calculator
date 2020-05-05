#pragma once

#ifndef _CALC_ALGORITHM_ABACKER_
#define _CALC_ALGORITHM_ABACKER_

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "Common.h"

using namespace std;

// #pragma warning(disable:4996)

#define LL long long
#define EPS 1e-10
#define MAX_OF_DENOMINATOR 100000LL

// 最大公约数
LL gcd(LL a, LL b) { return a == 0 ? b : gcd(b % a, a); }

// 最小公倍数
inline LL lcm(LL a, LL b) { return a / gcd(min(a, b), max(a, b)) * b; }

// 阶乘
LL factorial(LL x) {
    if (x == 0) return 1;
    bool negative = false;

    if (x < 0) {
        negative = true;
        x = -x;
    }

    LL ret = 1;
    for (int i = 1; i <= x; ++i) ret *= i;

    return negative ? -ret : ret;
}

// 返回a/b,检查除数b是否为0
inline double divCheck(double a, double b) {
    if (b == 0) throw runtime_error("Error:Bad Number For Division!");

    return a / b;
}

// 判断val是否为整数,精度(1e-10)
inline bool isInt(double val) {
    double d = val - round(val);
    return d > -(1e-10) && d < 1e-10;
}

// 将double类型转换为分数类型输出,有精度丢失
// 输出的数分母最大不超过MAX_OF_DENOMINATOR
bool doubleToFraction(double val) {
    if (!isInt(val)) {
        for (LL i = 2; i < MAX_OF_DENOMINATOR; ++i) {
            if (isInt(i * val)) {
                printf("%" LLD "/%" LLD, (LL)round(i * val), i);
                // cout << "\t" << round(i*val) << "/" << i;
                return true;
            }
        }
    }
    return false;
}

// (a^b)%mod
LL fastPow(LL a, LL b, LL mod) {
    LL ret = 1;
    a %= mod;
    while (b) {
        if (b & 1) {
            ret *= a;
            ret %= mod;
        }
        a *= a;
        a %= mod;
        b >>= 1;
    }
    return ret;
}

// 产生一个属于区间[s,t]的整数
inline int random(int s, int t) { return s + rand() % (t - s + 1); }

// 随机产生test个数测试val是否为素数
bool FermatTest(LL val, int test = 10000) {
    int seed;
    srand(unsigned(time(0)));
    for (int j = 0; j < test; ++j) {
        seed = random(2, 1000000);
        if ((seed % val > 0) && fastPow(seed, val - 1, val) != 1) {
            return false;
        }
    }
    return true;
}

// 判断val是否为素数,当数大于1e+9时采用费马测试,有一定误差!
bool isPrime(double val) {
    LL num = (LL)(val + EPS);
    if (num < 10 * 10000 * 10000) {
        if ((num & 1) == 0) return false;
        int _num = (int)num;
        int bd = (int)sqrt(_num) + 1;
        for (int i = 3; i < bd; i += 2)
            if (_num % i == 0) return false;
        return true;
    } else
        return FermatTest(num);
}

// 将num以n位小数输出
inline void printRadix(double num, unsigned int n) {
    char format[10];
    sprintf(format, "\t%%.%uf\n", n);
    printf(format, num);
}

// 将num以十六进制输出
inline void printHex(double num) { cout << "\t" << hex << (LL)num << endl; }

#endif
