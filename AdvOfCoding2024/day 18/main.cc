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
#include <deque>
#include <climits>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <functional>
#include <cmath>
#include <bitset>
#include <random>
#include <chrono>
using namespace std;

int dik(vector<vector<char>> grid, int x, int y){
    int gridSize = grid.size();
    vector<vector<int>> dist(gridSize, vector<int>(gridSize, INT_MAX));
    dist[y][x] = 0;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
    pq.push({0,{x,y}});
    while(!pq.empty()){
        auto [d, cord] = pq.top();
        pq.pop();
        auto [x,y] = cord;
        if(x == gridSize-1 && y == gridSize-1){
            return d;
        }
        for(auto dir : dirs){
            int nx = x + dir.first;
            int ny = y + dir.second;
            if(nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize && grid[ny][nx] != '#'){
                int newDist = d + 1;
                if(newDist < dist[ny][nx]){
                    dist[ny][nx] = newDist;
                    pq.push({newDist,{nx,ny}});
                }
            }
        }
    }
    return -1;
}

int adv(vector<pair<int,int>> cords){
    // turns cords into 2d vecotr
    int maxX = 0, maxY = 0;
    for(const auto& cord : cords) {
        maxX = max(maxX, cord.first);
        maxY = max(maxY, cord.second);
    }
    int gridSize = max(maxX, maxY) + 1;

    vector<vector<char>> grid(gridSize, vector<char>(gridSize, '.'));
    // for(int i = 0; i < cords.size(); i++){
    //     grid[cords[i].second][cords[i].first] = '#';
    // }
    for(int i = 0; i < cords.size(); i++){
        grid[cords[i].second][cords[i].first] = '#';
    }
    // prints out grid to check
    // for(auto row : grid){
    //     for(auto cell : row){
    //         cout << cell;
    //     }
    //     cout << endl;
    // }

    // Dikstra's algorithm to find shortest path from top left to bottom right

    return dik(grid,0,0);
}

pair<int,int> adv2(vector<pair<int,int>> cords, int bit){
    // turns cords into 2d vecotr
    int maxX = 0, maxY = 0;
    for(const auto& cord : cords) {
        maxX = max(maxX, cord.first);
        maxY = max(maxY, cord.second);
    }
    int gridSize = max(maxX, maxY) + 1;

    vector<vector<char>> grid(gridSize, vector<char>(gridSize, '.'));

    for(int i = 0; i < bit; i++){
        grid[cords[i].second][cords[i].first] = '#';
    }

    int cur = dik(grid,0,0);
    for(int i = bit; i < cords.size(); i++){
        grid[cords[i].second][cords[i].first] = '#';
        cur = dik(grid,0,0);
        if(cur == -1){
            return cords[i];
        }
    }

    return make_pair(-1,-1);
}

vector<pair<int, int>> parse(const string& filename) {
    vector<pair<int, int>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "FUCK an ERROR opening file" << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int x, y;
        char comma;

        if (iss >> x >> comma >> y) {
            data.push_back(make_pair(x, y));
        } else {
            cout << "ERROR " << filename << " at " << line << endl;
        }
    }

    file.close();
    return data;
}

vector<pair<int,int>> shorten(vector<pair<int,int>> grid, int num){
    if(grid.size() <= num){
        return grid;
    }
    vector<pair<int,int>> newGrid;
    for(int i = 0; i < num; i++){
        newGrid.push_back(grid[i]);
    }
    return newGrid;
}

int main(){
    // pt1
    // vector<pair<int,int>> grid = parse("data.txt");
    // grid = shorten(grid, 1024);

    // int Answer = adv(grid);
    // cout << "Answer " << Answer << endl;


    // pt2
    vector<pair<int,int>> grid = parse("data.txt");

    pair<int,int> Answer = adv2(grid,12);
    cout << "Answer " << Answer.first << "," << Answer.second << endl;


    return 1;
}