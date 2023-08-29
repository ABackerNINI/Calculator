#pragma once

#ifndef _CALC_CALC_ABACKER_
#define _CALC_CALC_ABACKER_

#include "Cache.h"
#include "Common.h"
#include "Symbol.h"
#include <cstring>
#include <iostream>
#include <stack>

extern Cache cache;
extern std::stack<char> OPTR;
extern std::stack<double> OPND;

bool SpecialCMD(std::string &s);
double Calc(std::string expr, bool isCache = true);

#endif
