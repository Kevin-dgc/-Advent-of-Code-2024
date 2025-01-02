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
#include <chrono>
using namespace std;


int adv(){
    
}


vector<vector<char>> parse(string filename){
    vector<vector<char>> grid;
    ifstream file(filename);
    if(!file.is_open()){
        cout << "FUCK an ERROR opening file" << endl;
        return grid;
    }
    string line;
    while(getline(file, line)){
        vector<char> row;
        for(char c : line){
            if(c != ' '){ // Exclude white spaces
                row.push_back(c);
            }
        }
        grid.push_back(row);
    }
    file.close();

    return grid;
}


int main(){
    vector<vector<char>> grid = parse("data.txt");

    int Answer = adv();
    cout << "Answer " << Answer << endl;
    return 1;
}