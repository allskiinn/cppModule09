#include "../includes/PmergeMe.hpp"


int main (int ac, char **av)
{
    if (ac < 2 )
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::vector<int> vec;
    std::deque<int> deq;
    PmergeMe a;
    double vectorSortingTime;
    double dequeSortingTime;
    for (int i = 1; i < ac; i++)
    {
        std::string s(av[i]);
        if (s.empty())
            return (std::cerr << "Error" << std::endl, 1);
        // somente inteiros positivos (sem sinais)
        for (size_t k = 0; k < s.size(); ++k)
        {
            if (s[k] < '0' || s[k] > '9')
                return (std::cerr << "Error" << std::endl, 1);
        }
        std::stringstream ss(s);
        long n = -1;
        ss >> n;
        if (!ss.eof() || ss.fail() || n <= 0 || n > INT_MAX)
            return (std::cerr << "Error" << std::endl, 1);
        vec.push_back((int)n);
        deq.push_back((int)n);
    }

    std::cout << "Before: ";
    PmergeMe::printVector(vec);
    a.caluclateTime(vec, deq , vectorSortingTime, dequeSortingTime);
    std::cout << "After: ";
    PmergeMe::printVector(vec);
    std::cout << "Time to process a range of " <<  ac - 1 <<  " elements with std::vector : " << vectorSortingTime << " us" << std::endl;
    std::cout << "Time to process a range of " <<  ac - 1 <<  " elements with std::deque :  " << dequeSortingTime << " us" << std::endl;
    return 0;
}