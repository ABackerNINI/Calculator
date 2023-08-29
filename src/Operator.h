#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include <string>
#include <vector>

class Operator {
  public:
    Operator(const std::string &operatorName, int priority, int operandNum)
        : operatorName(operatorName), priority(priority), operandNum(operandNum) {}

    const std::string &getOperatorName() const { return operatorName; }
    int getPriority() const { return priority; }
    int getOperandNum() const { return operandNum; }

  private:
    std::string operatorName;
    int priority;
    int operandNum;
};

class Operators {
  public:
    Operators();
    Operator find(const std::string &operatorName);
    Operator operator[](size_t i) const { return operators[i]; }
    size_t size() const { return operators.size(); }

  private:
    std::vector<Operator> operators;
};

#endif // __OPERATOR_H__
