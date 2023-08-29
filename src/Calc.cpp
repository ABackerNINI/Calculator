/**
 * Calc V2
 *
 * By ABacker 9/18/2015
 */

#include "Calc.h"
#include "Algorithm.h"
#include "Common.h"
#include <cstring>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

Cache cache;
std::stack<char> OPTR;
std::stack<double> OPND;
Operators OPERATORS;

double Calc(std::string expr, bool isCache) {
    precondition(expr);

    while (!OPTR.empty())
        OPTR.pop();
    while (!OPND.empty())
        OPND.pop();

    OPTR.push(endSym()); // #

    int size = (int)expr.size();
    // if (s.back() == '=')--size;

    for (int i = 0; i < size; ++i) {
        if (expr[i] == ' ' || expr[i] == '=') {
            continue;
        } else if (isLtr(expr[i])) { // 变量
            OPND.push(cache.get(getVar(expr, i)));
        } else if (isNum(expr[i])) {
            OPND.push(getFigure(expr, i)); // 数字
        } else if (expr[i] == ',') {
            while (GetTop(OPTR, false) != '(')
                Calc(OPTR, OPND);
        } else if (expr[i] == '(') {
            OPTR.push('(');
        } else if (expr[i] == ')') {
            while (GetTop(OPTR, false) != '(') {
                Calc(OPTR, OPND);
            }
            GetTop(OPTR);
        } else { // 符号
            while (Prio(expr[i]) <= Prio(GetTop(OPTR, false))) {
                Calc(OPTR, OPND);
            }
            OPTR.push(expr[i]);
        }
    }

    while (GetTop(OPTR, false) != endSym()) { // #
        Calc(OPTR, OPND);
    }

    if (OPTR.size() > 1 || OPND.size() > 1) {
        throw std::runtime_error("Error: Wrong Expression! Redundant operand(s).");
    }
    if (isCache) {
        cache.push(GetTop(OPND, false));
        cache.printLastPush();
    }

    return GetTop(OPND, false);
}
