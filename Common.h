#pragma once

#ifndef _CALC_COMMON_ABACKER_
#define _CALC_COMMON_ABACKER_

#include <stack>
#include <string>
#include <iostream>

#ifdef _WIN32
#define LLD "I64d"
#else
#define LLD "lld"
#endif

// 获取string s在位置pos处的数字,并推进pos至数字最后一位
double getFigure(const std::string &s, int &pos);

// 获取string s在位置pos处的变量名,并推进pos至变量名最后一位
std::string getVar(const std::string &s, int &pos);

// 获取string s在位置pos处的变量名
std::string getVar(const std::string &s, int &&pos);

//////////////////////////////////////////////////////////////////////////////

// 去除所有空格
void RemoveSpaces(std::string &s);

//////////////////////////////////////////////////////////////////////////////

// 判断是否为数字
inline bool isNum(char c) { return c >= '0' && c <= '9'; }

// 判断是否为字母
inline bool isLtr(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// 判断是否为大写字母
inline bool isCap(char c) { return c >= 'A' && c <= 'Z'; }

// 判断栈顶是否为空
template <typename T>
inline T GetTop(std::stack<T> &st, bool rid = true) {
    if (st.empty()) throw std::runtime_error("Error:Wrong Expression!");

    if (rid) {
        T ret = st.top();
        st.pop();
        return ret;
    } else
        return st.top();
}

#endif
