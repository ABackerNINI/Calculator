#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>

#include "Common.h"
#include "Algorithm.h"

class Cache {
   public:
    Cache() : autoStrNum(0) {}
    // 为push进的数分配一个变量名
    void push(double num) {
        std::string str;
        do {
            str = "";
            str += ((autoStrNum++) % 26) + 'A';
        } while (used.count(str));

        data[str] = num;
        lastPush = str;
    }
    // 将num映射到str上
    void set(const std::string &str, double num) {
        data[str] = num;
        if (used.count(str) == 0) {
            used.insert(str);
            _str.push_back(str);
        }
        lastPush = str;
    }
    // 获取str对应的num
    double get(const std::string &str) const {
        if (used.count(str) || (str.size() == 1 && isCap(str[0]))) {
            return data.at(str);
        } else {
            std::string e = "Error: '" + str + "' is NOT initialized!";
            throw std::runtime_error(e);
        }
    }
    // 打印上次push进的数据
    void printLastPush() const {
        std::cout << "\t" << lastPush << " <- ";  // << data[lastPush];
        printf("%.6f\t", data.at(lastPush));
        doubleToFraction(data.at(lastPush));
        std::cout << std::endl;
    }
    // 打印全部数据
    void printAll() const {
        for (unsigned int i = 0; i < _str.size(); ++i) {
            std::cout << "\t" << _str[i] << ": " << data.at(_str[i]);
            if ((i + 1) % 7 == 0) std::cout << std::endl;
        }
        std::cout << std::endl;
    }

   private:
    std::string lastPush;
    int autoStrNum;
    std::vector<std::string> _str;
    std::set<std::string> used;
    std::map<std::string, double> data;
};

#endif
