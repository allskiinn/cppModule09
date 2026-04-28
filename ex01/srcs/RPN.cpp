#include "../includes/RPN.hpp"
#include <cctype>
#include <sstream>

RPN::RPN(){}
RPN::~RPN(){}
RPN& RPN::operator=(const RPN &src) {
    if (this != &src) {
        this->numbers = src.numbers; 
    }
    return *this;
}
RPN::RPN(const RPN &src) {
    this->numbers = src.numbers;
}

void RPN::calc(std::string input)
{
	while (!numbers.empty())
		numbers.pop();

	std::stringstream ss(input);
	std::string token;

	while (ss >> token)
	{
		if (token.size() != 1)
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		char c = token[0];
		if (std::isdigit(c))
		{
			numbers.push(c - '0');
			continue;
		}
		if (c != '+' && c != '-' && c != '*' && c != '/')
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		if (numbers.size() < 2)
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		double b = numbers.top(); numbers.pop();
		double a = numbers.top(); numbers.pop();
		if (c == '+')
			numbers.push(a + b);
		else if (c == '-')
			numbers.push(a - b);
		else if (c == '*')
			numbers.push(a * b);
		else
		{
			if (b == 0.0)
			{
				std::cerr << "Error" << std::endl;
				return;
			}
			numbers.push(a / b);
		}
	}

	if (numbers.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return;
	}
	std::cout << numbers.top() << std::endl;
}
