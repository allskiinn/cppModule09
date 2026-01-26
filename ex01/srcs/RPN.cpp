#include "../includes/RPN.hpp"
#include <cctype>

RPN::~RPN(){}
RPN& RPN::operator=(const RPN &src) {
    if (this != &src) {
        this->result = src.result;
        this->Stack = src.Stack; 
    }
    return *this;
}
RPN::RPN(const RPN &src) {
    this->result = src.result;
    this->Stack = src.Stack;
}

bool RPN::operatorIsValid(char Operator)
{
	if (Operator == '/' || Operator == '+' || Operator == '-'
		|| Operator == '*')
		return (true);
	else
		return (false);
}

int RPN::checkRpn(std::string &rpn, int index)
{
	if (!isdigit(rpn[index]) && rpn[index] != ' ' && operatorIsValid(rpn[index]) == false && rpn[index] != ' ')
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	if ((index == 0 || index == 2) && !isdigit(rpn[index]))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	else if (isdigit(rpn[index]) && rpn[index + 1] != ' ')
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	else if ((index != 0) && isdigit(rpn[index]) && rpn[index + 1] == ' ' && !operatorIsValid(rpn[index + 2]))
	{
		std::cerr << 0 << std::endl;
		return (1);
	}
	else if (operatorIsValid(rpn[index]) && rpn[index + 1] != ' '
			&& rpn[index + 1] != 0)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	else if (operatorIsValid(rpn[index]) && Stack.size() < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	else if (operatorIsValid(rpn[index]) && rpn[index + 1] == 0 && Stack.size() < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}

RPN::RPN(std::string rpn) : result(0)
{
	int valid = 0;
	double second, first;
	for (int index = 0; rpn[index]; index++)
	{
		if (checkRpn(rpn, index) == 1){ valid = 1; break ;} ;
		if (isdigit(rpn[index]))
			Stack.push(rpn[index] - 48);
		else if (Stack.size() >= 2 && operatorIsValid(rpn[index]) == true)
		{
			second = Stack.top();
			Stack.pop();
			first = Stack.top();
			Stack.pop();
			if (rpn[index] == '/' && second == 0)
			{
				std::cerr << "Error" << std::endl;
				valid = 1;
				break ;
			}
			result = (rpn[index] == '+') ? (first
				+ second ): (rpn[index] == '-') ? (first
				- second) : (rpn[index] == '*') ? (first
				* second) : (first / second);
			Stack.push(result);
		}
	}
	if (valid == 0)
		if (Stack.size() == 1)
			std::cout << Stack.top() << std::endl;
}