#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
#include <utility>
#include <cctype>
#include <sstream> 
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <functional>
#include <cmath>
#include <bitset>
#include <random>
#include <tuple>
#include <chrono>

using namespace std;

// Directions and corresponding movements (0: up, 1: right, 2: down, 3: left)
const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct State {
    int x, y, direction, cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int calculate_turn_cost(int current_dir, int new_dir) {
    int diff = abs(current_dir - new_dir);
    return (diff == 0) ? 0 : (diff == 2 ? 2000 : 1000);
}

int find_shortest_path(const vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Start and end positions
    int start_x = rows - 2, start_y = 1;
    int end_x = 1, end_y = cols - 2;

    // Priority queue for A* (min-heap based on cost)
    priority_queue<State, vector<State>, greater<State>> pq;

    // Visited states (x, y, direction) -> cost
    unordered_map<string, int> visited;

    // Push initial state (starting position facing "up" - direction 0)
    pq.push({start_x, start_y, 0, 0});

    auto encode_state = [](int x, int y, int dir) {
        return to_string(x) + "," + to_string(y) + "," + to_string(dir);
    };

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        // If we reached the end, return the cost
        if (current.x == end_x && current.y == end_y) {
            return current.cost;
        }

        // Encode the current state
        string state_key = encode_state(current.x, current.y, current.direction);

        // Skip if already visited with a lower cost
        if (visited.count(state_key) && visited[state_key] <= current.cost) {
            continue;
        }

        visited[state_key] = current.cost;

        // Try all possible movements
        for (int new_dir = 0; new_dir < 4; ++new_dir) {
            int new_x = current.x + directions[new_dir].first;
            int new_y = current.y + directions[new_dir].second;

            // Check if the move is valid
            if (new_x < 0 || new_x >= rows || new_y < 0 || new_y >= cols || grid[new_x][new_y] == '#') {
                continue;
            }

            int turn_cost = calculate_turn_cost(current.direction, new_dir);
            int move_cost = (current.direction == new_dir) ? 1 : 0;
            int new_cost = current.cost + turn_cost + move_cost;

            pq.push({new_x, new_y, new_dir, new_cost});
        }
    }

    // If no path is found, return -1
    return -1;
}

vector<vector<char>> parse(string filename) {
    ifstream file(filename);
    vector<vector<char>> grid;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return grid;
    }

    string line;
    while (getline(file, line)) {
        // Remove any trailing whitespace
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (!line.empty()) {
            grid.push_back(vector<char>(line.begin(), line.end()));
        }
    }

    file.close();

    // Validate grid dimensions
    if (!grid.empty()) {
        size_t cols = grid[0].size();
        for (const auto& row : grid) {
            if (row.size() != cols) {
                cerr << "Error: Inconsistent row lengths in grid." << endl;
                return {};
            }
        }
    }

    return grid;
}

int main() {
    vector<vector<char>> grid = parse("data.txt");

    // Debugging: Check grid dimensions and content
    if (grid.empty()) {
        cout << "Error: Parsed grid is empty or invalid." << endl;
        return -1;
    }

    cout << "Parsed Grid Dimensions: " << grid.size() << "x" << grid[0].size() << endl;
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }

    int Answer = find_shortest_path(grid);
    cout << "Answer " << Answer << endl;
    return 1;
}
