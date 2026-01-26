#ifndef RPN_H
#define RPN_H

#include <string>
#include <stack>
#include <iostream>

class RPN
{
    private:
        double result;
        std::stack<double> Stack;
        RPN();
    public:
        RPN(std::string rpn);
        RPN(const RPN &src);
        RPN & operator=(const RPN &src);
        ~RPN();
        bool operatorIsValid(char Operator);
        int checkRpn(std::string &rpn, int index);
};
#endif
