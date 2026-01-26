
#include "../includes/RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "invalid number of argumnts" << std::endl;
		return (1);
	}
	RPN rpn(av[1]);
	return (0);
}
