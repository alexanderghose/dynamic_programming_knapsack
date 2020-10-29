#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// assume 0 <= i <= 100, and 0 <= capacity <= 100
vector<vector<int>> cache(100, std::vector<int>(100, -1)); // memoization we store the max value for a given i and current_capacity.

// return max value of selected items. w = weights, v = values, c = remaining capacity/maxweight. i = current item
int getMaxValue(vector<int>& weights, vector<int>& values, int capacity, int i) {
	if (i == weights.size() || capacity <= 0) return 0;
	if (cache[i][capacity] > -1) {
		return cache[i][capacity];
	}

	if (weights[i] < capacity) { // can include
		cache[i][capacity] = std::max(values[i] + getMaxValue(weights, values, capacity - weights[i], i+1),getMaxValue(weights, values, capacity, i+1));
		return cache[i][capacity];
	} else {
		cache[i][capacity] = getMaxValue(weights, values, capacity, i + 1);
		return cache[i][capacity];
	}
}

int main()
{
	vector<int> weights = { 2,4,3,5,5 };
	vector<int> values = { 3,4,1,2,6 };
	int capacity = 12;

	cout << getMaxValue(weights, values, capacity, 0);
}