#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cctype>
using namespace std;


int adv(vector<vector<char>> input){
    int sum = 0;

    // Horizontal
    // int counter = 0;
    // bool forwards = true;

    for(int row = 0; row < input.size(); row++){
        for(int col = 0; col < input[row].size()-3; col++){
            char c1 = input[row][col];
            char c2 = input[row][col+1];
            char c3 = input[row][col+2];
            char c4 = input[row][col+3];

            if(c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S'){
                sum++;
            }
            else if(c1 == 'S' && c2 == 'A' && c3 == 'M' && c4 == 'X'){
                sum++;
            }
        }
    }


    // Vertical
    // counter = 0;
    // forwards = true;

    for(int col = 0; col < input[0].size(); col++){
        for(int row = 0; row < input.size()-3; row++){
            char c1 = input[row][col];
            char c2 = input[row+1][col];
            char c3 = input[row+2][col];
            char c4 = input[row+3][col];

            if(c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S'){
                sum++;
            }
            else if(c1 == 'S' && c2 == 'A' && c3 == 'M' && c4 == 'X'){
                sum++;
            }
        }
    }


    // Diagonal right
    /*
       /
      /
     /   
    */
   
    for(int row = 0; row < input.size()-3; row++){
        for(int col = input[row].size()-1; col >= 3; col--){
            char c1 = input[row][col];
            char c2 = input[row+1][col-1];
            char c3 = input[row+2][col-2];
            char c4 = input[row+3][col-3];

            if(c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S'){
                sum++;
            }
            else if(c1 == 'S' && c2 == 'A' && c3 == 'M' && c4 == 'X'){
                sum++;
            }
        }
    }

    // Diagonal left
    /*
    \
     \
      \
    */
   
    for(int row = 0; row < input.size()-3; row++){
        for(int col = 0; col < input[row].size()-3; col++){
            char c1 = input[row][col];
            char c2 = input[row+1][col+1];
            char c3 = input[row+2][col+2];
            char c4 = input[row+3][col+3];

            if(c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S'){
                sum++;
            }
            else if(c1 == 'S' && c2 == 'A' && c3 == 'M' && c4 == 'X'){
                sum++;
            }
        }
    }
    return sum;
}

int adv2(vector<vector<char>> input){
    int sum = 0;

    for(int row = 0; row < input.size()-2; row++){
        for(int col = 0; col < input[row].size()-2; col++){
            // used for '\' 
            char origin = input[row][col];
            char bottomRight = input[row+2][col+2];
             
            // used for both '\' and '/'
            char middle = input[row+1][col+1];

            // used for '/'
            char bottomLeft = input[row+2][col];
            char topRight = input[row][col+2];

            if(middle == 'A'){
                // check for '\'
                if((origin == 'M' && bottomRight == 'S') || (origin == 'S' && bottomRight == 'M')){
                    // check for '/'
                    if ((bottomLeft == 'M' && topRight == 'S') || (bottomLeft == 'S' && topRight == 'M')){
                    sum++;
                    }
                }
            }
        }
    }

    return sum;
}






vector<vector<char>> readGrid(const string& filename) {
    ifstream file(filename);
    vector<vector<char>> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }
    return grid;
}

int main(){
    vector<vector<char>> Input = readGrid("data.txt");
    vector<vector<char>> TestInput = {
        {'M', 'M', 'M', 'S', 'X', 'X', 'M', 'A', 'S', 'M'},
        {'M', 'S', 'A', 'M', 'X', 'M', 'S', 'M', 'S', 'A'},
        {'A', 'M', 'X', 'S', 'X', 'M', 'A', 'A', 'M', 'M'},
        {'M', 'S', 'A', 'M', 'A', 'S', 'M', 'S', 'M', 'X'},
        {'X', 'M', 'A', 'S', 'A', 'M', 'X', 'A', 'M', 'M'},
        {'X', 'X', 'A', 'M', 'M', 'X', 'X', 'A', 'M', 'A'},
        {'S', 'M', 'S', 'M', 'S', 'A', 'S', 'X', 'S', 'S'},
        {'S', 'A', 'X', 'A', 'M', 'A', 'S', 'A', 'A', 'A'},
        {'M', 'A', 'M', 'M', 'M', 'X', 'M', 'M', 'M', 'M'},
        {'M', 'X', 'M', 'X', 'A', 'X', 'M', 'A', 'S', 'X'}
    };

    //int dis = adv(TestInput);
    //int dis = adv(Input);

    //int dis = adv2(TestInput);
    int dis = adv2(Input);
    cout << "dis " << dis << endl;

}