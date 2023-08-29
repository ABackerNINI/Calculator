#include "Common.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stack>

// 获取string s在位置pos处的数字,并推进pos至数字最后一位
double getFigure(const std::string &s, int &pos) {
    double fig = s[pos] - '0';
    int point = -1;
    while ((s[++pos] >= '0' && s[pos] <= '9') || s[pos] == '.') {
        if (s[pos] == '.')
            point = 0;
        else {
            if (~point)
                ++point;
            fig = fig * 10 + s[pos] - '0';
        }
    }
    --pos;

    return ~point ? fig / pow((long long)10, (long long)point) : fig;
}

// 获取string s在位置pos处的变量名,并推进pos至变量名最后一位
std::string getVar(const std::string &s, int &pos) {
    std::string str = "";
    while (s[pos] == ' ')
        ++pos;
    while (isLtr(s[pos])) {
        str += s[pos++];
    }
    --pos;

    return str;
}

// 获取string s在位置pos处的变量名
std::string getVar(const std::string &s, int &&pos) {
    std::string str = "";
    while (s[pos] == ' ')
        ++pos;
    while (isLtr(s[pos])) {
        str += s[pos++];
    }
    --pos;

    return str;
}

// 获取string s在位置pos处的符号,并推进pos
/*string getSym(const string &s, int &pos){
        string tmp;tmp += s[pos];
}*/

void RemoveSpaces(std::string &s) {
    size_t len = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (!isspace(s[i])) {
            s[len++] = s[i];
        }
    }
    s.resize(len);
}
