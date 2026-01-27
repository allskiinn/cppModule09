
#include "../includes/RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "invalid number of argumnts" << std::endl;
		return (1);
	}
	RPN a;
	std::string in = av[1];
	a.calc(in);
	return (0);
}
