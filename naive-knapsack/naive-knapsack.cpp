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

int bottom_up_codealong(vector<int>& in_weights, vector<int>& in_values, int C) {
	vector<vector<int>> dp_table(100, vector<int>(100, 0)); // init a 100x100 array
	// we want i+1 rows representing #items, and C columns representing various capacities
	// so that at the end of the table-filling, we can have a resolution to the decision problem based on resolutions to smaller decision problms
	for (int i = 0; i <= in_weights.size(); i++) {
		for (int j = 0; j <= C; j++) {
			cout << "looking at #items i=" << i << " for capacity=" << j;
			if (i == 0 || j == 0) {
				cout << ". zeroing...";
				dp_table[i][j] = 0;
			} else if (in_weights[i-1] > j) { // if the weight of this item is greater than the capacity
				cout << ". weight of current item=" << in_weights[i-1] << " > current_capacity.";
				dp_table[i][j] = dp_table[i - 1][j];
			} else {
				cout << ". looking up max...";
				dp_table[i][j] = std::max(
					dp_table[i - 1][j], // exclude current item
					in_values[i-1] + dp_table[i - 1][j - in_weights[i-1]] // gain some value, lose some capacity. where does the i-1 come from?
				);
			}
			cout << " . value=" << dp_table[i][j] << endl;
		}
	}
	return dp_table[in_weights.size()][C];
}

int main()
{
	vector<int> weights = { 2,4,3,5,5 };
	vector<int> values = { 3,4,1,2,6 };
	int capacity = 12;

	//cout << getMaxValue(weights, values, capacity, 0); // <-- top-down
	cout << bottom_up_codealong(weights, values, capacity);
}