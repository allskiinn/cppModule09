#ifndef P_HPP
#define P_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <climits>

class PmergeMe
{
  public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe& operator=(const PmergeMe& other);
    PmergeMe(const PmergeMe& other);

    void runVector(std::vector<int> &vec);
    void runDeque(std::deque<int> &deq);
    void caluclateTime(std::vector<int> &vec, std::deque <int> &deq, double &vecTime, double &deqTime);

    static void printVector(const std::vector<int> &vec);
};

#endif