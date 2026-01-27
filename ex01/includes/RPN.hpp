#ifndef RPN_H
#define RPN_H

#include <string>
#include <stack>
#include <iostream>

class RPN
{
    private:
        std::stack<double> numbers;
    public:
        RPN();
        RPN(const RPN &src);
        RPN & operator=(const RPN &src);
        ~RPN();
        void calc(std::string input);
};
#endif
