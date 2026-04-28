#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::~PmergeMe(){}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	(void)other;
}

namespace {

struct Node
{
	int value;
	int pairIndex; // -1 para straggler
	bool isMax;
	Node() : value(0), pairIndex(-1), isMax(false) {}
	Node(int v, int idx, bool m) : value(v), pairIndex(idx), isMax(m) {}
};

struct Pair
{
	int min;
	int max;
	int idx;
	Pair() : min(0), max(0), idx(0) {}
	Pair(int a, int b, int i) : min(a), max(b), idx(i) {}
};

static void mergePairsByMax(std::vector<Pair> &pairs, int l, int mid, int r)
{
	std::vector<Pair> left(mid - l + 1);
	std::vector<Pair> right(r - mid);
	for (int i = 0; i < (mid - l + 1); ++i) left[i] = pairs[l + i];
	for (int j = 0; j < (r - mid); ++j) right[j] = pairs[mid + 1 + j];

	int i = 0, j = 0, k = l;
	while (i < (int)left.size() && j < (int)right.size())
	{
		if (left[i].max <= right[j].max)
			pairs[k++] = left[i++];
		else
			pairs[k++] = right[j++];
	}
	while (i < (int)left.size()) pairs[k++] = left[i++];
	while (j < (int)right.size()) pairs[k++] = right[j++];
}

static void sortPairsByMax(std::vector<Pair> &pairs, int l, int r)
{
	if (l >= r) return;
	int mid = l + (r - l) / 2;
	sortPairsByMax(pairs, l, mid);
	sortPairsByMax(pairs, mid + 1, r);
	mergePairsByMax(pairs, l, mid, r);
}

static size_t findMaxPos(const std::vector<Node> &mainChain, int pairIdx)
{
	for (size_t i = 0; i < mainChain.size(); ++i)
	{
		if (mainChain[i].isMax && mainChain[i].pairIndex == pairIdx)
			return i;
	}
	return mainChain.size();
}

static size_t lowerBoundByValue(const std::vector<Node> &mainChain, int value, size_t hi)
{
	size_t lo = 0;
	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
		if (mainChain[mid].value < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	return lo;
}

static std::vector<size_t> buildJacobsthalOrder(size_t n)
{
	std::vector<size_t> order;
	if (n == 0) return order;

	std::vector<size_t> jac;
	jac.push_back(0);
	jac.push_back(1);
	while (jac.back() < n)
		jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);

	size_t prev = 1;
	for (size_t k = 2; k < jac.size(); ++k)
	{
		size_t curr = jac[k];
		if (curr > n) curr = n;
		for (size_t i = curr; i > prev; --i)
			order.push_back(i);
		prev = jac[k];
		if (prev > n) prev = n;
		if (prev == n) break;
	}
	return order;
}

static std::vector<int> fordJohnsonSortToVector(const std::vector<int> &input)
{
	if (input.size() <= 1)
		return input;

	std::vector<Pair> pairs;
	pairs.reserve(input.size() / 2);
	bool hasStraggler = (input.size() % 2) != 0;
	int straggler = 0;

	int pairIdx = 0;
	for (size_t i = 0; i + 1 < input.size(); i += 2)
	{
		int a = input[i];
		int b = input[i + 1];
		if (a <= b) pairs.push_back(Pair(a, b, pairIdx));
		else pairs.push_back(Pair(b, a, pairIdx));
		++pairIdx;
	}
	if (hasStraggler)
		straggler = input.back();

	if (!pairs.empty())
		sortPairsByMax(pairs, 0, (int)pairs.size() - 1);

	std::vector<Node> mainChain;
	mainChain.reserve(input.size());
	if (!pairs.empty())
	{
		mainChain.push_back(Node(pairs[0].min, pairs[0].idx, false));
		mainChain.push_back(Node(pairs[0].max, pairs[0].idx, true));
		for (size_t i = 1; i < pairs.size(); ++i)
			mainChain.push_back(Node(pairs[i].max, pairs[i].idx, true));
	}

	size_t minsCount = (pairs.size() > 0) ? (pairs.size() - 1) : 0;
	std::vector<size_t> order = buildJacobsthalOrder(minsCount);

	for (size_t oi = 0; oi < order.size(); ++oi)
	{
		size_t idx1 = order[oi];
		size_t pairPos = idx1;
		if (pairPos >= pairs.size())
			continue;

		int pIdx = pairs[pairPos].idx;
		size_t hi = findMaxPos(mainChain, pIdx);
		if (hi == mainChain.size())
			hi = mainChain.size();
		size_t pos = lowerBoundByValue(mainChain, pairs[pairPos].min, hi);
		mainChain.insert(mainChain.begin() + pos, Node(pairs[pairPos].min, pIdx, false));
	}

	for (size_t i = 1; i < pairs.size(); ++i)
	{
		int pIdx = pairs[i].idx;
		bool found = false;
		for (size_t k = 0; k < mainChain.size(); ++k)
		{
			if (!mainChain[k].isMax && mainChain[k].pairIndex == pIdx)
			{
				found = true;
				break;
			}
		}
		if (found) continue;
		size_t hi = findMaxPos(mainChain, pIdx);
		size_t pos = lowerBoundByValue(mainChain, pairs[i].min, hi);
		mainChain.insert(mainChain.begin() + pos, Node(pairs[i].min, pIdx, false));
	}

	if (hasStraggler)
	{
		size_t pos = lowerBoundByValue(mainChain, straggler, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, Node(straggler, -1, false));
	}

	std::vector<int> out;
	out.reserve(mainChain.size());
	for (size_t i = 0; i < mainChain.size(); ++i)
		out.push_back(mainChain[i].value);
	return out;
}

}

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

void PmergeMe::runVector(std::vector<int> &vec)
{
	std::vector<int> sorted = fordJohnsonSortToVector(vec);
	vec.swap(sorted);
}

void PmergeMe::runDeque(std::deque<int> &deq)
{
	std::vector<int> tmp;
	tmp.reserve(deq.size());
	for (std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it)
		tmp.push_back(*it);

	std::vector<int> sorted = fordJohnsonSortToVector(tmp);
	deq.assign(sorted.begin(), sorted.end());
}

void PmergeMe::printVector(const std::vector<int> &vec)
{
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}