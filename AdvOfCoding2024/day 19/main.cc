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

int check(string s, map<string,bool>& mapOfPatterns){
    int curPattern = -1;
    string longest = "";
    for(int i = 0; i <= s.length(); i++){
        string sub = s.substr(0, i);
        if(mapOfPatterns[sub] == true){
            curPattern = i;
            longest = sub;
        }
    }
    return curPattern;
}

bool patternExists(string s, map<string,bool>& mapOfPatterns){
    // go threw each word entire length but keep a index of where the last correct one was
    // back one then redo search

    int curIndex = -1;
    int index = 0;
    int count = 0;
    for(int i = 0; i < s.length();){
        curIndex = -1;
        // checks the cur thing and all to the right of it
        for(int j = count; j < s.length(); j++){
            string sub = s.substr(i-count, j);
            if(mapOfPatterns[sub] == true){
                curIndex = j;
            }
        }

        if(curIndex == -1 && i <= 0){
            return false;
        }
        // add alot of couts to check when it starts inf loop 
        // then add sometype of base case to break out of inf loop maybe after s.length times?
        if(curIndex == -1){
            count++;
        }
        else{
            count = 0;
        }
        i += curIndex; // brwrr -> wrr should be whats left
    }

    return true;
 }



int adv(vector<string> input, vector<string> list){
    map<string,bool> mapOfPatterns;
    for(string s : input){
        mapOfPatterns[s] = true;
    }

    int sum = 0;

    for(int i = 0; i < list.size(); i++){
        string s = list[i];
        //cout << "Full String is: " << s << endl;
        bool failed = false;
        if(patternExists(s, mapOfPatterns)){
            sum++;
            failed = true;
        }
        string outCome = "Success";
        if(!failed){
            outCome = "Failed";
        }

        cout << "  " << s << "            Sum: " << sum  << " " << outCome<< endl;
    }

    return sum;
}


pair<vector<string>,vector<string>> parse(string filename) {
    pair<vector<string>, vector<string>> result;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "FUCK an ERROR opening file" << endl;
        return result;
    }
    
    string line;
    vector<string> first;
    vector<string> second;
    bool firstLine = true;
    
    while(getline(file, line)) {
        if(firstLine) {
            stringstream ss(line);
            string pattern;
            
            while(getline(ss, pattern, ',')) {
                pattern.erase(0, pattern.find_first_not_of(" \r\n"));
                pattern.erase(pattern.find_last_not_of(" \r\n") + 1);

                if(!pattern.empty()) {
                    first.push_back(pattern);
                }
            }
            firstLine = false;
        }
        else {
            line.erase(0, line.find_first_not_of(" \r\n"));
            line.erase(line.find_last_not_of(" \r\n") + 1);
            
            if(!line.empty()) {
                second.push_back(line);
            }
        }
    }

    file.close();
    return make_pair(first,second);
}

int main(){
    pair<vector<string>,vector<string>> grid = parse("test2.txt");

    vector<string> input = grid.first;;
    vector<string> list = grid.second;
   
    // prints out grid
    // for(string l : input){
    //     cout << l << "";
    // }

    // cout << endl;
    // for (string l : list) {
    //     cout << l << endl;
    // }


    int Answer = adv(input, list);
    cout << "Answer " << Answer << endl;
    return 0;
}