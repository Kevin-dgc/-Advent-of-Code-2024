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

int sumIt(vector<char> operations, vector<int> list){
    int sum = list[0]; 
    for(int i = 1; i < list.size(); i++){
        if(operations[i-1] == '+'){
            sum += list[i];
        }
        else if(operations[i-1] == '*'){
            sum *= list[i];
        }
    }
    return sum;  
}

bool allSum(int wanted, vector<int> list){
    vector<char> operations(list.size() - 1, '+');
    int totalcombo = 1 << list.size()-1;
    for(int i = 0; i < totalcombo; i++){
        for(int j = 0; j < list.size()-1; j++){
            if(i & (1 << j)){
                operations[j] = '*';
            }
            else{
                operations[j] = '+';
            }
        }
        if(sumIt(operations,list) == wanted){
            return true;
        }
    }
    return false;
}

int adv(vector<pair<int, vector<int>>> input){
    int sum = 0;
    for(int i = 0; i < input.size(); i++){
        if(allSum(input[i].first,input[i].second)){
            sum += input[i].first;
        }        
    }
    return sum;
}

int main(){
    vector<pair<int, vector<int>>> TestInput = {
        {190, {10, 19}},
        {3267, {81, 40, 27}},
        {83, {17, 5}},
        {156, {15, 6}},
        {7290, {6, 8, 6, 15}},
        {161011, {16, 10, 13}},
        {192, {17, 8, 14}},
        {21037, {9, 7, 18, 13}},
        {292, {11, 6, 16, 20}}
    };
    int dis = adv(TestInput);
    cout << "dis " << dis << endl;
}
