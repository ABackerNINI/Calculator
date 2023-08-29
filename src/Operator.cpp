#include "Operator.h"
#include <algorithm>
#include <iostream>

Operators::Operators() {
    operators = {Operator{"+", 2, 2},      Operator{"-", 2, 2},   Operator{"*", 3, 2},      Operator{"/", 3, 2},
                 Operator{"++", 2, 1},     Operator{"--", 2, 1},  Operator{"**", 4, 2},     Operator{"//", 4, 2},
                 Operator{"%", 3, 2},      Operator{"pow", 5, 2}, Operator{"sqrt", 5, 1},   Operator{"sin", 5, 1},
                 Operator{"cos", 5, 1},    Operator{"tan", 5, 1}, Operator{"arcsin", 5, 1}, Operator{"arccos", 5, 1},
                 Operator{"arctan", 5, 1}, Operator{"gcd", 5, 2}, Operator{"lcm", 5, 2},    Operator{"ln", 5, 1},
                 Operator{"log", 5, 2},    Operator{"^", 1, 2},   Operator{"|", 1, 2},      Operator{"&", 1, 2},
                 Operator{"~", 1, 1},      Operator{"!", 6, 1},   Operator{"'", 6, 1},      Operator{"arc'", 5, 1},
                 Operator{"#", 0, 0}};
    std::sort(operators.begin(), operators.end(),
              [](const Operator &a, const Operator &b) { return a.getOperatorName() < b.getOperatorName(); });
    for (auto &op : operators) {
        std::cout << op.getOperatorName() << std::endl;
    }
}

Operator Operators::find(const std::string &operatorName) {
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i].getOperatorName() == operatorName) {
            return operators[i];
        }
    }
    return Operator("", -1, -1);
}
