#pragma once

#ifndef _CALC_CALC_ABACKER_
#define _CALC_CALC_ABACKER_

#include <stack>
#include <cstring>
#include <iostream>

#include "Cache.h"
#include "Symbol.h"
#include "Common.h"

Cache cache;
std::stack<char> OPTR;
std::stack<double> OPND;

double Calc(std::string expr, bool isCache = true);

#endif
