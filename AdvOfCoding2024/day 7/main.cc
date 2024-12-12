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
#include <cmath>
using namespace std;



//check each combo of operaters
// if the equation equals the first value then sum++, contine 
// else keep going until end of list of combos



long long sumIt(vector<char> operations, vector<long long> list){
    long long sum = list[0]; 
    
    // for(long long i = 0; i < list.size(); i++){
    //     cout << list[i] << " ";
    // }
    // cout << endl;

    for(long long i = 1; i < list.size(); i++){
        if(operations[i-1] == '+'){
            sum += list[i];
        }
        else if(operations[i-1] == '*'){
            sum *= list[i];
        }
        else if(operations[i-1] == '|'){
            string sumS = to_string(sum);
            string nextS = to_string(list[i]);
            string combined = sumS + nextS;
            sum = stoll(combined);
        }
    }

    //cout << "\n~~~~~~~~~" << endl;
    //cout << sum << endl;
    return sum;  
}


bool allSum(long long wanted, vector<long long> list){
    vector<char> operations(list.size() - 1, '+');

    long long totalcombo = pow(3,list.size());
    //cout << "~~~~~~~~~~~~~~~~~~~" << endl;

    for(long long i = 0; i < totalcombo; i++){
        for(long long j = 0; j < list.size()-1; j++){
            long long num = (i / (long long)pow(3, j)) % 3;
            if(num == 0){
                operations[j] = '*';
            }
            else if(num == 1){
                operations[j] = '+';
            }
            else{
                operations[j] = '|';
            }
        }

        // for(long long p = 0; p < operations.size(); p++){
        //     cout << operations[p] << " ";
        // }
        // cout << endl;

        if(sumIt(operations,list) == wanted){
            return true;
        }
    }
    // check is opp is equal to wanted
    return false;
}

long long adv(vector<pair<long long, vector<long long>>> input){
    long long sum = 0;

    for(long long i = 0; i < input.size(); i++){
        if(allSum(input[i].first,input[i].second)){
            sum += input[i].first;
        }        
    }

    return sum;
}

int main(){
    ifstream file("data.txt");  // Replace with your actual file path
    vector<pair<long long, vector<long long>>> Input;
    string line;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        long long key;
        ss >> key;  // Read the first integer as the key
        vector<long long> values;
        long long value;

        // Skip the colon and space after the key
        ss.ignore(2);

        // Read the rest of the integers and store them in the values vector
        while (ss >> value) {
            values.push_back(value);
        }

        // Check if the vector has been populated before pushing to the pair
        if (!values.empty()) {
            Input.push_back(make_pair(key, values));
        } else {
            cout << "Warning: No values found for key " << key << endl;
        }
    }





    vector<pair<long long, vector<long long>>> TestInput = {
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

    //long long dis = adv(TestInput);
    long long dis = adv(Input);
    cout << "dis " << dis << endl;

}