#include "Algorithm.h"

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

#include "Common.h"

// 最大公约数
LL gcd(LL a, LL b) { return a == 0 ? b : gcd(b % a, a); }

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

// 随机产生test个数测试val是否为素数
bool FermatTest(LL val, int test) {
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
        for (int i = 3; i < bd; i += 2) {
            if (_num % i == 0) return false;
        }
        return true;
    } else {
        return FermatTest(num);
    }
}
