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




bool correctOrder(vector<pair<int, int>> rules, vector<int> input){
    // check each num one by one
    // find all instances of the num in the rules on the first 
    // then check that all seconds are past it (index)

    // find all instances of the num in the rules on the second 
    // then check that all first are past it (index)

    // do for all nums then return true if failed anywhere return false
    for(int index = 0; index < input.size(); index++){
        int curNum = input[index];
        
        vector<int> rightNum;
        vector<int> leftNum;

        for(vector<pair<int, int>>::iterator it = rules.begin(); it != rules.end(); it++){
            if(it->first == curNum){
                rightNum.push_back(it->second);
            }
            if(it->second == curNum){
                leftNum.push_back(it->first);
            }
        }

        for(int i = 0; i < input.size(); i++){
            int num = input[i];
            if(num != curNum){
                if(find(rightNum.begin(), rightNum.end(), num) != rightNum.end()){
                    if(index > i){
                        //cout << index << endl;
                        return false;
                    }
                }
                else if(find(leftNum.begin(), leftNum.end(), num) != leftNum.end()){
                    if(index < i){
                        //cout << index << endl;
                        return false;
                    }
                }
            } 
        }
    }
    //cout << "done" << endl;
    return true;
}

int orderIt(vector<pair<int, int>> rules, vector<int> input){
    vector<int> sorted;

    vector<int> leftPair; // 1 | 2 -> 1 -> 1 is before 2
    vector<int> rightPair; // 1 | 2 -> 2 - > 2 is before 1

    for(auto it = rules.begin(); it != rules.end(); it++){
        leftPair.push_back(it->first);
        rightPair.push_back(it->second);

    }


    for(int index = 0; index < input.size(); index++){
        int curNum = input[index];
        if(index == 0){
            sorted.push_back(curNum);
        }
        else{
            vector<int> leftIndex;
            for(int i = 0; i < leftPair.size(); i++){
                if(find(sorted.begin(), sorted.end(), leftPair[i]) != sorted.end()){
                    leftIndex.push_back(leftPair[i]);
                }
            }

            vector<int> rightIndex;
            for(int i = 0; i < rightPair.size(); i++){
                if(find(sorted.begin(), sorted.end(), rightPair[i]) != sorted.end()){
                    rightIndex.push_back(rightPair[i]);
                }
            }
            

            sort(rightIndex.begin(), rightIndex.end());
            sort(leftIndex.begin(), leftIndex.end());

            if(leftIndex.size() == 0 && rightIndex.size() == 0){
                sorted.push_back(curNum);
            }
            else{
                int target = 0;
                if(rightIndex.size() > 0){
                    target = rightIndex[0]-1;
                }
                if(leftIndex.size() > 0){
                    int max = leftIndex[leftIndex.size()-1];

                    while(target < max){
                        target++;
                    }
                }
                sorted.insert(sorted.begin() + target, curNum);   
            }

                  
        }
    }
    int count = 0;
    for (int num : sorted) {
        count++;
    }

    return sorted[count/2];
}

int orderIt2(vector<pair<int, int>> rules, vector<int> input) {
    vector<int> sorted;

    // Iterate through each input number
    for (int index = 0; index < input.size(); index++) {
        int curNum = input[index];
        bool inserted = false;

        // Try to find the correct position to insert curNum
        for (int i = 0; i <= sorted.size(); i++) {
            bool canInsert = true;

            // Check if inserting curNum at position i violates any rule
            for (auto& rule : rules) {
                int left = rule.first;
                int right = rule.second;

                // If curNum is left in the rule and inserting it at position i places it after the right element, it's invalid
                if (curNum == left && i < sorted.size() && sorted[i] == right) {
                    canInsert = false;
                    break;
                }

                // If curNum is right in the rule and inserting it at position i places it before the left element, it's invalid
                if (curNum == right && i > 0 && sorted[i - 1] == left) {
                    canInsert = false;
                    break;
                }
            }

            // If no rule is violated, insert curNum
            if (canInsert) {
                sorted.insert(sorted.begin() + i, curNum);
                inserted = true;
                break;
            }
        }

        // If no valid position was found, append the element at the end
        if (!inserted) {
            sorted.push_back(curNum);
        }
    }
    
    int count = 0;
    for (int num : sorted) {
        count++;
    }
    return sorted[count/2]; 
}


int adv(vector<pair<int, int>> rules, vector<vector<int>> input){
    int sum = 0;

    for(int i = 0; i < input.size(); i++){
        if(correctOrder(rules,input[i])){
            //comment out for pt 2
            //int mid = input[i].size()/2;
            //sum += input[i][mid];
        }
        // uncomment out else for pt 2
        else{
            int mid = orderIt2(rules,input[i]);
            sum += mid;
        }
    }

    return sum;
}



int main(){
    
    vector<pair<int, int>> Rules;
    ifstream file("rules.txt");
    if (!file) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string left, right;

        if (getline(iss, left, '|') && getline(iss, right)) {
            int first = stoi(left);
            int second = stoi(right);
            Rules.emplace_back(first, second);
        }
    }

    file.close();

    vector<vector<int>> Input;
    ifstream file2("input.txt");
    if (!file2) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line2;
    while (getline(file2, line2)) {
        vector<int> row2;
        istringstream iss2(line2);
        string number2;

        while (getline(iss2, number2, ',')) {
            row2.push_back(stoi(number2));
        }

        Input.push_back(row2);
    }

    file2.close();

    
    
    vector<pair<int, int>> TestRules = {
        {47, 53},
        {97, 13},
        {97, 61},
        {97, 47},
        {75, 29},
        {61, 13},
        {75, 53},
        {29, 13},
        {97, 29},
        {53, 29},
        {61, 53},
        {97, 53},
        {61, 29},
        {47, 13},
        {75, 47},
        {97, 75},
        {47, 61},
        {75, 61},
        {47, 29},
        {75, 13},
        {53, 13}
    };

    std::vector<std::vector<int>> TestInput = {
        {75, 47, 61, 53, 29},
        {97, 61, 53, 29, 13},
        {75, 29, 13},
        {75, 97, 47, 61, 53},
        {61, 13, 29},
        {97, 13, 75, 29, 47}
    };
    
    //int dis = adv(TestRules, TestInput);
    int dis = adv(Rules, Input);
    cout << "dis " << dis << endl;

    return 0;
}