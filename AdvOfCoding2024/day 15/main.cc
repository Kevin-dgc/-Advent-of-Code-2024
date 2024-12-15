#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
#include <utility>
#include <stdexcept>
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
#include <chrono>
using namespace std;

vector<vector<char>> doubleSize(vector<vector<char>> grid){
    vector<vector<char>> NewGrid;
    
    for(int i = 0; i < grid.size(); i++){
        vector<char> temp;
        for(int j = 0; j < grid[i].size(); j++){
           if(grid[i][j] == '@'){
               temp.push_back(grid[i][j]);
                temp.push_back('.');
           }
           else if(grid[i][j] == 'O'){
                temp.push_back('[');
                temp.push_back(']');
           }
           else{
                temp.push_back(grid[i][j]);
                temp.push_back(grid[i][j]);
           }
        }
        NewGrid.push_back(temp);
    }


    return NewGrid;
}

bool canMove(vector<vector<char>>& grid, int x, int y, char move){
    if(move == '<'){
        // attempt to move left
        if(grid[x][y-1] == '#'){
            return false;
        }
        else if (grid[x][y-1] == '.'){
            swap(grid[x][y], grid[x][y-1]);
            return true;
        }
        else{
            if(canMove(grid, x, y-1, move)){
                swap(grid[x][y], grid[x][y-1]);
                return true;
            }
        }
    }
    else if(move == '>'){
        // attempt to move right
        if(grid[x][y+1] == '#'){
            return false;
        }
        else if (grid[x][y+1] == '.'){
            swap(grid[x][y], grid[x][y+1]);
            return true;
        }
        else{
            if(canMove(grid, x, y+1, move)){
                swap(grid[x][y], grid[x][y+1]);
                return true;
            }
        }
    }
    else if(move == '^'){
        // attempt to move up
        if(grid[x-1][y] == '#'){
            return false;
        }
        else if (grid[x-1][y] == '.'){
            swap(grid[x][y], grid[x-1][y]);
            return true;
        }
        else{
            if(canMove(grid, x-1, y, move)){
                swap(grid[x][y], grid[x-1][y]);
                return true;
            }
        }
    }
    else if(move == 'v'){
        // attempt to move down
        if(grid[x+1][y] == '#'){
            return false;
        }
        else if (grid[x+1][y] == '.'){
            swap(grid[x][y], grid[x+1][y]);
            return true;
        }
        else{
            if(canMove(grid, x+1, y, move)){
                swap(grid[x][y], grid[x+1][y]);
                return true;
            }
        }
    }
    else{
        return false;
    }
    return false;
}

bool canMove2(vector<vector<char>>& grid, int x, int y, char move){
    char cur = grid[x][y];
    vector<vector<char>> NewGrid = grid;

    if(move == '<'){
        // attempt to move left
        if(grid[x][y-1] == '#'){
            return false;
        }
        else if (grid[x][y-1] == '.'){
            if(cur == '@'){
                swap(grid[x][y], grid[x][y-1]);
                return true;
            }
            else{
                swap(grid[x][y], grid[x][y-1]);
                swap(grid[x][y], grid[x][y+1]);
                return true;
            }
            
        }
        else{
            if(canMove2(grid, x, y-2, move)){
                
                if(cur == '@'){
                    swap(grid[x][y], grid[x][y-1]);
                    return true;
                }
                else{
                    swap(grid[x][y], grid[x][y-1]);
                    swap(grid[x][y], grid[x][y+1]);
                    
                    return true;
                }
            }
        }
    }
    else if(move == '>'){
        // attempt to move right
        if(grid[x][y+1] == '#'){
            return false;
        }
        else if (grid[x][y+1] == '.'){
            if(cur == '@'){
                swap(grid[x][y], grid[x][y+1]);
                return true;
            }
            else{
                swap(grid[x][y], grid[x][y+1]);
                swap(grid[x][y], grid[x][y-1]);
                return true;
            }
        }
        else{
            if(canMove2(grid, x, y+2, move)){
                if(cur == '@'){
                    swap(grid[x][y], grid[x][y+1]);
                    return true;
                }
                else{
                    swap(grid[x][y], grid[x][y+1]);
                    swap(grid[x][y], grid[x][y-1]);
                    return true;
                }
            }
        }
        
    }
    else if(move == '^'){
        // attempt to move up       
        if(grid[x-1][y] == '#'){
            return false;
        }
        else if (grid[x-1][y] == '.'){
            swap(grid[x][y], grid[x-1][y]);
            return true;
        }
        else{
            if(NewGrid[x-1][y] == ']'){
                if(canMove2(NewGrid, x-1, y, move) && canMove2(NewGrid, x-1, y-1, move)){
                    swap(NewGrid[x][y], NewGrid[x-1][y]);
                    grid = NewGrid;
                    return true;
                }
            }
            else{
                if(canMove2(NewGrid, x-1, y, move) && canMove2(NewGrid, x-1, y+1, move)){
                    swap(NewGrid[x][y], NewGrid[x-1][y]);
                    grid = NewGrid;
                    return true;
                }
            }
        }   
    }
    else if(move == 'v'){
        // attempt to move down
        if(grid[x+1][y] == '#'){
            return false;
        }
        else if (grid[x+1][y] == '.'){
            swap(grid[x][y], grid[x+1][y]);
            return true;
        }
        else{
            if(NewGrid[x+1][y] == ']'){
                if(canMove2(NewGrid, x+1, y, move) && canMove2(NewGrid, x+1, y-1, move)){
                    swap(NewGrid[x][y], NewGrid[x+1][y]);
                    grid = NewGrid;
                    return true;
                }
            }
            else{
                if(canMove2(NewGrid, x+1, y, move) && canMove2(NewGrid, x+1, y+1, move)){
                    swap(NewGrid[x][y], NewGrid[x+1][y]);
                    grid = NewGrid;
                    return true;
                }
            }
        }
    }
    return false;
}

int adv(vector<vector<char>>& grid, vector<char> moves){
    // find @
    int x = 0, y = 0;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    for(int i = 0; i < moves.size(); i++){
        if(canMove(grid, x, y, moves[i])){
            if(moves[i] == '<'){
                y--;
            }
            else if(moves[i] == '>'){
                y++;
            }
            else if(moves[i] == '^'){
                x--;
            }
            else if(moves[i] == 'v'){
                x++;
            }
        }

        // print out display of grid
        // for(int i = 0; i < grid.size(); i++){
        //     for(int j = 0; j < grid[i].size(); j++){
        //         cout << grid[i][j];
        //     }
        //     cout << endl;
        // }
    }

    // find speical checkSum for Grid
    // (100 * y) + x, y and x are indexs of O
    int sum = 0;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == 'O'){
                sum += (100 * i) + j;
            }
        }
    }

    // for(int i = 0; i < grid.size(); i++){
    //     for(int j = 0; j < grid[i].size(); j++){
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    return sum;
}

int adv2(vector<vector<char>>& grid, vector<char> moves){
    // find @
    int x = 0, y = 0;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    for(int i = 0; i < moves.size(); i++){
        if(canMove2(grid, x, y, moves[i])){ // only line that is different from adv
            if(moves[i] == '<'){
                y--;
            }
            else if(moves[i] == '>'){
                y++;
            }
            else if(moves[i] == '^'){
                x--;
            }
            else if(moves[i] == 'v'){
                x++;
            }
        }

        // print out display of grid
        // for(int i = 0; i < grid.size(); i++){
        //     for(int j = 0; j < grid[i].size(); j++){
        //         cout << grid[i][j];
        //     }
        // }

    }

    // find speical checkSum for Grid
    // (100 * y) + x, y and x are indexs of O
    int sum = 0;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '['){
                //cout << "i " << i << " j " << j << endl;
                sum += (100 * i) + (j);
            }
        }
    }

    // for(int i = 0; i < grid.size(); i++){
    //     for(int j = 0; j < grid[i].size(); j++){
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    return sum;
}

pair<vector<vector<char>>, vector<char>> parse(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "FUCK an ERROR opening file" << endl;
    }

    vector<vector<char>> grid;
    vector<char> sequence;
    string line;
    bool readingSequence = false;

    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        // Check if it's time to switch to reading the sequence
        if (!readingSequence && (line[0] == '<' || line[0] == '>' || line[0] == '^' || line[0] == 'v')) {
            readingSequence = true;
        }

        if (readingSequence) {
            // Add characters from this line to the sequence
            sequence.insert(sequence.end(), line.begin(), line.end());
        } else {
            // Add the grid line as a vector of characters
            grid.push_back(vector<char>(line.begin(), line.end()));
        }
    }

    file.close();

    // Return the parsed grid and sequence as a pair
    return make_pair(grid, sequence);
}

int main(){
   pair<vector<vector<char>>, vector<char>> data = parse("data.txt");

    // for pt 1

    // int Answer = adv(data.first, data.second);
    // cout << "Answer " << Answer << endl;
    // return 1;

    // for pt 2
    data.first = doubleSize(data.first);
    
    // for(auto i : data.first){
    //     for(auto j : i){
    //         cout << j;
    //     }
    //     cout << endl;
    // }

    int Answer = adv2(data.first, data.second);
    cout << "Answer " << Answer << endl;
    return 1;

}