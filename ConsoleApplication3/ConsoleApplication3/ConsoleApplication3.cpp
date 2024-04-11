#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include <random>

using namespace std;

int assignmentProblem(const vector<vector<int>>& costMatrix) {
    int n = costMatrix.size();
    int minCost = numeric_limits<int>::max();
    vector<int> assignment(n);

    for (int i = 0; i < n; ++i) {
        assignment[i] = i;
    }
    // todo loop over all assignments==permutations and find minimum 

    while (next_permutation(assignment.begin(), assignment.end())); {
        int cost = 0;
        for (int i = 0; i < assignment.size(); ++i) {
            cost += costMatrix[i][assignment[i]];
        }
        if (cost < minCost) {
            minCost = cost;
        }
    }

    return minCost;
}

vector<vector<int>> generateMatrix(int n, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(minVal, maxVal);

    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = distribution(gen);
        }
    }

    return result;
}

int main()
{
    vector<vector<int>> testCostMatrix = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    vector<vector<int>> bigCostMatrix = generateMatrix(13, 0, 100);

    auto star = std::chrono::high_resolution_clock::now();
    int vys = assignmentProblem(bigCostMatrix);
    auto en = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duratio = en - star;
    std::cout << "Time: " << duratio.count() << " sec" << std::endl;

    cout << vys << std::endl;

    return 0;

}
