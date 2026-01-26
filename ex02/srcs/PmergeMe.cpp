#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(){};
PmergeMe::~PmergeMe(){};
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this == &other) {
        return *this; 
    }
    return *this;
};
PmergeMe::PmergeMe(const PmergeMe& other){
    (void)(other);
};

void PmergeMe::mergeInsertSortVector(std::vector<int> &vec, int start, int end)
{
    int newEnd;
    if (start < end)
    {
        if ((end - start) < 10)
            insertSortVector(vec, start, end);
        else
        {
            newEnd = start + (end - start) / 2;
            mergeInsertSortVector(vec,  start, newEnd);
            mergeInsertSortVector(vec, newEnd + 1, end);
            mergeSortVector(vec, start, newEnd, end);
        }
    }
};

void PmergeMe::mergeSortVector(std::vector<int> &vec, int start, int mid, int end)
{
    int i, j , k;

    std::vector<int> left(mid - start + 1);
    std::vector<int> right(end - mid);

    for(i = 0; i < (mid - start + 1); ++i)
        left[i] = vec[start + i];
    for(j = 0; j < (end - mid); ++j)
        right[j] = vec[mid + 1 + j];
    i = 0;
    j = 0;
    k = start;
    while(i < (mid - start + 1) && j < (end - mid))
    {
        if (left[i] <= right[j])
            vec[k++] = left[i++];
        else
            vec[k++] = right[j++];
    }

    while(i < (mid - start + 1))
        vec[k++] =  left[i++];
    while (j < (end - mid))
        vec[k++] = right[j++];
};

void PmergeMe::insertSortVector(std::vector<int> &vec, int start, int end)
{
    for(int index = (start + 1); index <= end; index++)
    {
        int hold = vec[index];
        int j = index - 1;
        for(; j >= start && vec[j] > hold; --j)
            vec[j + 1] = vec[j];
        vec[j + 1] = hold;
    }
};

void PmergeMe::runVector(std::vector<int> &vec)
{
    mergeInsertSortVector(vec, 0, vec.size() - 1);
};

void PmergeMe::runDeque(std::deque<int> &deq)
{
    mergeInsertSortDeque(deq, 0, deq.size() - 1);
};

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq, int start, int end)
{
    int newEnd;
    if (start < end)
    {
        if ((end - start) < 10)
            insertSortDeque(deq, start, end);
        else
        {
            newEnd = start + (end - start) / 2;
            mergeInsertSortDeque(deq,  start, newEnd);
            mergeInsertSortDeque(deq, newEnd + 1, end);
            mergeSortDeque(deq, start, newEnd, end);
        }
    }
};

void PmergeMe::mergeSortDeque(std::deque<int> &deq, int start, int mid, int end)
{
    int i, j , k;

    std::deque<int> left(mid - start + 1);
    std::deque<int> right(end - mid);

    for(i = 0; i < (mid - start + 1); ++i)
        left[i] = deq[start + i];
    for(j = 0; j < (end - mid); ++j)
        right[j] = deq[mid + 1 + j];
    i = 0;
    j = 0;
    k = start;
    while(i < (mid - start + 1) && j < (end - mid))
    {
        if (left[i] <= right[j])
            deq[k++] = left[i++];
        else
            deq[k++] = right[j++];
    }

    while(i < (mid - start + 1))
        deq[k++] =  left[i++];
    while (j < (end - mid))
        deq[k++] = right[j++];
};

void PmergeMe::insertSortDeque(std::deque<int> &deq, int start, int end)
{
    for(int index = (start + 1); index <= end; index++)
    {
        int hold = deq[index];
        int j = index - 1;
        for(; j >= start && deq[j] > hold; --j)
            deq[j + 1] = deq[j];
        deq[j + 1] = hold;
    }
};

void PmergeMe::caluclateTime(std::vector<int> &vec, std::deque<int> &deq, double &vecTime, double &deqTime)
{
    std::clock_t start = std::clock();
    PmergeMe::runVector(vec);
    std::clock_t end = std::clock();
    double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC / 1000000.0);
    vecTime = elapsed;
    start = std::clock();
    PmergeMe::runDeque(deq);
    end = std::clock();
    elapsed = static_cast<double> (end - start) / (CLOCKS_PER_SEC / 1000000.0);
    deqTime = elapsed;
    
}

void PmergeMe::showDeq(std::deque<int> &deq)
{

    static int i = 0;

    if (!i)
        std::cout << "Before: ";
    else
        std::cout << "After: "; 

    typedef typename std::deque<int>::const_iterator deq_iterator;
    for (deq_iterator Dit = deq.begin(); Dit != deq.end(); ++Dit)
		std::cout << *Dit << " ";
    std::cout << std::endl;
    i++;
}

void PmergeMe::showVec(std::vector<int> &vec)
{

    static int i = 0;

    if (!i)
        std::cout << "Before: ";
    else
        std::cout << "After: "; 

    typedef typename std::vector<int>::const_iterator vec_iterator;
    for (vec_iterator Vit = vec.begin(); Vit != vec.end(); ++Vit)
		std::cout << *Vit << " ";
    std::cout << std::endl;
    i++;
}