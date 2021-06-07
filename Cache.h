#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Common.h"
#include "Algorithm.h"

class Cache {
   public:
    Cache() : autoStrNum(0){};
    // 为push进的数分配一个变量名
    void push(double num) {
        std::string str;
        do {
            str = "";
            str += ((autoStrNum++) % 26) + 'A';
        } while (used[str]);

        data[str] = num;
        lastPush = str;
    }
    // 将num映射到str上
    void set(const std::string &str, double num) {
        data[str] = num;
        used[str] = true;

        _str.push_back(str);
        lastPush = str;
    }
    // 获取str对应的num
    double get(const std::string &str) {
        if (used[str] || (str.size() == 1 && isCap(str[0])))
            return data[str];
        else {
            std::string e = "Error: '" + str + "' is NOT initialized!";
            throw std::runtime_error(e.data());
        }
    }
    // 打印上次push进的数据
    void printLastPush() {
        std::cout << "\t" << lastPush << " <- ";  // << data[lastPush];
        printf("%.6f\t", data[lastPush]);
        doubleToFraction(data[lastPush]);
        std::cout << std::endl;
    }
    // 打印全部数据
    void printAll() {
        for (unsigned int i = 0; i < _str.size(); ++i) {
            std::cout << "\t" << _str[i] << ": " << data[_str[i]];
            if ((i + 1) % 7 == 0) std::cout << std::endl;
        }
        std::cout << std::endl;
    }

   private:
    std::string lastPush;
    int autoStrNum;
    std::vector<std::string> _str;
    std::map<std::string, bool> used;
    std::map<std::string, double> data;
};

#endif
