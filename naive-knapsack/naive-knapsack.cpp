#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// return max value of selected items. w = weights, v = values, c = remaining capacity/maxweight. i = current item
int getMaxValue(vector<int>& weights, vector<int>& values, int capacity, int i) {
	if (i == weights.size() || capacity <= 0) return 0;

	if (weights[i] < capacity) { // can include
		return std::max(values[i] + getMaxValue(weights, values, capacity - weights[i], i+1),
			getMaxValue(weights, values, capacity, i+1));
	} else {
		return getMaxValue(weights, values, capacity, i + 1);
	}
}

int main()
{
	vector<int> weights = { 2,4,3,5,5 };
	vector<int> values = { 3,4,1,2,6 };
	int capacity = 12;

	cout << getMaxValue(weights, values, capacity, 0);
}