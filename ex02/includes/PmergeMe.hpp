#ifndef P_HPP
#define P_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <sstream>

class PmergeMe
{
    private:
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe& operator=(const PmergeMe& other);
        PmergeMe(const PmergeMe& other);
        
        void mergeInsertSortVector(std::vector<int> &vec, int start, int end);
        void mergeSortVector(std::vector<int> &vec, int start, int mid, int end);
        void insertSortVector(std::vector<int> &vec, int start, int end);

        void mergeInsertSortDeque(std::deque<int> &deq, int start, int end);
        void mergeSortDeque(std::deque<int> &deq, int start, int mid, int end);
        void insertSortDeque(std::deque<int> &deq, int start, int end);
        
        void runVector(std::vector<int> &vec);
        void runDeque(std::deque<int> &deq);

        void showVec(std::vector<int> &vec);
        void showDeq(std::deque<int> &deq);
        void caluclateTime(std::vector<int> &vec, std::deque <int> &deq, double &vecTime, double &deqTime);
};

#endif