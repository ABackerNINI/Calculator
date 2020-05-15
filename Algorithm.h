#pragma once

#ifndef _CALC_ALGORITHM_ABACKER_
#define _CALC_ALGORITHM_ABACKER_

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "Common.h"

#define LL long long
#define EPS 1e-10
#define MAX_OF_DENOMINATOR 100000LL

// 最大公约数
LL gcd(LL a, LL b);

// 阶乘
LL factorial(LL x);

// 将double类型转换为分数类型输出,有精度丢失
// 输出的数分母最大不超过MAX_OF_DENOMINATOR
bool doubleToFraction(double val);

// (a^b)%mod
LL fastPow(LL a, LL b, LL mod);

// 随机产生test个数测试val是否为素数
bool FermatTest(LL val, int test = 10000);

// 判断val是否为素数,当数大于1e+9时采用费马测试,有一定误差!
bool isPrime(double val);

//////////////////////////////////////////////////////////////////////////////

// 最小公倍数
inline LL lcm(LL a, LL b) {
    return a / gcd(std::min(a, b), std::max(a, b)) * b;
}

// 返回a/b,检查除数b是否为0
inline double divCheck(double a, double b) {
    if (b == 0) throw std::runtime_error("Error:Bad Number For Division!");

    return a / b;
}

// 判断val是否为整数,精度(1e-10)
inline bool isInt(double val) {
    double d = val - round(val);
    return d > -(1e-10) && d < 1e-10;
}

// 产生一个属于区间[s,t]的整数
inline int random(int s, int t) { return s + rand() % (t - s + 1); }

// 将num以n位小数输出
inline void printRadix(double num, unsigned int n) {
    char format[10];
    sprintf(format, "\t%%.%uf\n", n);
    printf(format, num);
}

// 将num以十六进制输出
inline void printHex(double num) {
    std::cout << "\t" << std::hex << (LL)num << std::endl;
}

#endif
