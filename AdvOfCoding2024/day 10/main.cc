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
using namespace std;

bool good(pair<int, int> location, vector<vector<int>>& map, int cur) {
    int x = location.first;
    int y = location.second;
    return x >= 0 && x < map.size() && y >= 0 && y < map[0].size() && map[x][y] == cur + 1;
}

int pathFinder(pair<int,int> location, vector<vector<int>>& map, vector<vector<bool>>& visited){
    int cur = map[location.first][location.second];
    visited[location.first][location.second] = true;

    if(cur == 9){
        return 1;
    }

    vector<pair<int, int>> directions = {
        {location.first - 1, location.second}, // up
        {location.first + 1, location.second}, // down
        {location.first, location.second - 1}, // left
        {location.first, location.second + 1}  // right
    };
    
    visited[location.first][location.second] = true;
    int total = 0;
    for(auto& direction : directions){
        if(good(direction, map, cur) && !visited[direction.first][direction.second]){
            total += pathFinder(direction, map, visited);
        }
    }
    return total;   
}


int adv(vector<vector<int>> map){
    int sum = 0;

    for(int i = 0; i < map.size();i++){
        for(int j = 0; j < map[i].size();j++){
            if(map[i][j] == 0){
                vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
                int cur = pathFinder(make_pair(i,j),map,visited);
                cout << cur << " ";
                sum += cur;
            }
        }
    }

    return sum;
}

int pathFinder2(pair<int,int> location, vector<vector<int>>& map){
    int cur = map[location.first][location.second];

    if(cur == 9){
        return 1;
    }

    vector<pair<int, int>> directions = {
        {location.first - 1, location.second}, // up
        {location.first + 1, location.second}, // down
        {location.first, location.second - 1}, // left
        {location.first, location.second + 1}  // right
    };
    
    int total = 0;
    for(auto& direction : directions){
        if(good(direction, map, cur)){
            total += pathFinder2(direction, map);
        }
    }
    return total;   
}

int adv2(vector<vector<int>> map){
    int sum = 0;

    for(int i = 0; i < map.size();i++){
        for(int j = 0; j < map[i].size();j++){
            if(map[i][j] == 0){
                vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
                int cur = pathFinder2(make_pair(i,j),map);
                cout << cur << " ";
                sum += cur;
            }
        }
    }

    return sum;
}

int main(){
    ifstream file("data.txt");
    if(!file.is_open()){
        cout << "FUCK an ERROR opening file" << endl;
        return -1;
    }

    vector<vector<int>> map;
    string line;
    while(getline(file, line)){
        vector<int> row;
        for(auto& c : line){
            row.push_back(c - '0');
        }
        map.push_back(row);
    }
    for(int i = 0; i < map.size()-1;i++){
        map[i].pop_back();
    }

    for(auto& row : map){
        for(auto& c : row){
            cout << c << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    int dis = adv2(map);
    cout << "dis " << dis << endl;
    return 1;
}