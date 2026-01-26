#include "../includes/PmergeMe.hpp"


int main (int ac, char **av)
{
    if (ac < 2 )
    {
        std::cerr << "Missing args" << std::endl;
        return 1;
    }
    std::vector<int> vec;
    std::deque<int> deq;
    PmergeMe a;
    double vectorSortingTime;
    double dequeSortingTime;
    int number;
    for (int i = 1; i < ac; i++)
    {
        std::stringstream readstring(av[i]);
        if (!(readstring >> number) || !(readstring.eof()))
            break ;
        if (number < 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        vec.push_back(number);
        deq.push_back(number);
    }

    std::cout << std::endl;
    a.showVec(vec);
    a.caluclateTime(vec, deq , vectorSortingTime, dequeSortingTime);
    a.showVec(vec);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Time to process a range of " <<  ac - 1 <<  " elements with std::vector : " << vectorSortingTime << " us" << std::endl;
    std::cout << "Time to process a range of " <<  ac - 1 <<  " elements with std::deque :  " << dequeSortingTime << " us" << std::endl;
    return 0;
}