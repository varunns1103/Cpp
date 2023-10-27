#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int value;
    double ratio;  // Value-to-weight ratio
};

bool compare(Item i1, Item i2) {
    return (i1.ratio > i2.ratio);
}

class Knapsack {
private:
    vector<Item> items;
    int capacity;
    int currentWeight;
    int currentValue;
    int maxValue;

    // Recursive function to explore the solution space
    void branchAndBound(int level) {
        if (level == items.size()) {
            // Reached the leaf level, update the maximum value if needed
            if (currentValue > maxValue) {
                maxValue = currentValue;
            }
            return;
        }

        // Check if including the item at the current level is feasible
        if (currentWeight + items[level].weight <= capacity) {
            // Include the item
            currentWeight += items[level].weight;
            currentValue += items[level].value;

            // Recursively explore the left branch (include the item)
            branchAndBound(level + 1);

            // Backtrack (remove the item) before exploring the right branch
            currentWeight -= items[level].weight;
            currentValue -= items[level].value;
        }

        // Explore the right branch (exclude the item)
        branchAndBound(level + 1);
    }

public:
    Knapsack(vector<Item>& _items, int _capacity) : items(_items), capacity(_capacity) {
        currentWeight = 0;
        currentValue = 0;
        maxValue = 0;

    for (Item& item : items) {
            item.ratio = static_cast<double>(item.value) / item.weight;
        }
    }

    int solve() {
        // Sort items based on value-to-weight ratio (high ratio first)
        sort(items.begin(), items.end(), compare);

        // Start with level 0 (root) and explore the solution space
        branchAndBound(0);

        return maxValue;
    }
};

int main() {
    // Example items
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};

    int capacity = 50;

    // Create a Knapsack instance and solve the problem
    Knapsack knapsack(items, capacity);
    int maxProfit = knapsack.solve();

    cout << "Maximum Profit Earned: " << maxProfit << "\n";

    return 0;
}
