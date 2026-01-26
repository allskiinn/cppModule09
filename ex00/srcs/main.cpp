#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    if (ac > 2) {
        std::cout << "too many args" << std::endl;
        return (1);
    }
    try {
        BitcoinExchange  bitcoin;
        BitcoinExchange  b;

        b = bitcoin;
        b.validInputFile(av[1]);
        // b.showMap();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}