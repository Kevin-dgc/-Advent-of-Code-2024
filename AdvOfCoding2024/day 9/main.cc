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

int ctoi(char c){
    return c- '0';
}

int adv(vector<int> list){
    // take the vector<int> and make it into the 0..1.... vector<string>
    vector<string> myList;
    int counter = 0;
    
    for(int index = 0; index < list.size(); index+=2){
        for(int i = 0; i < list[index]; i++){
            myList.push_back(to_string(counter));
        }

        if(index+1 < list.size()){
            for(int j = 0; j < list[index+1]; j++){
                myList.push_back(".");
            }
            counter++;
        }
    }

    // print out what you have
    // for(string str : myList){
    //     cout << str;
    // } cout << endl;


    // swap . and num from left and right end until ~sorted
    int left = 0;
    int right = myList.size();

    while(left < right){

        for(int i = 0; i < myList.size(); i++){
            if(myList[i] == "."){
                left = i;
                break;
            }
        }

        for(int i = myList.size()-1; i >= 0; i--){
            if(myList[i] != "."){
                right = i;
                break;
            }
        }

        if(left < right){
            //swap
            string temp = myList[left];
            myList[left] = myList[right];
            myList[right] = temp;
        }


        //print out what you have
        // for(string str : myList){
        //     cout << str;
        // } cout << endl;
    }
    //print out what you have
    // for(string str : myList){
    //     cout << str;
    // } cout << endl;

    // go threw vector<string> until you hit .
    // and add to sum cur*index
    //return sum
    int sum = 0;

    for(int i = 0; i < myList.size() && myList[i] != "."; i++){
        sum += stoi(myList[i]) * i;
    }


    return sum;
}

long long adv2(vector<int> list){
    // take the vector<int> and make it into the 0..1.... vector<string>
    vector<string> myList;
    int counter = 0;
    
    for(int index = 0; index < list.size(); index+=2){
        myList.push_back("{");
        for(int i = 0; i < list[index]; i++){
            myList.push_back(to_string(counter));
            myList.push_back(",");   
        }
        myList.pop_back();
        myList.push_back("}");
        if(index+1 < list.size()){
            for(int j = 0; j < list[index+1]; j++){
                myList.push_back(".");
            }
            counter++;
        }
    }

    // for(string str : myList){
    //     cout << str;
    //     //cout << endl;
    // }
    // cout << endl;


    // {0,0}...{1,1,1}...{2}...{3,3,3}.{4,4}.{5,5,5,5}.{6,6,6,6}.{7,7,7,7}.{8,8,8,8,8}{9,9}

    //swaping time
    int max = counter;
    
    
    cout << "myList size: " << myList.size() << endl;
    cout << "max: " << max << endl;

    
    while(max >= 0){
        bool found = false;
        int length = 0;
        int dotSize = 0;
        int leftDotIndex = 0;
        int rightNumIndex = myList.size();

        //redo right
        for(int i = 0; i < myList.size(); i++){
            string cur = myList[i];
            if(cur != "," && cur != "}" && cur != "{" && cur != "." && stoi(cur) == max){
                rightNumIndex = i;
                break;
            }
        }

        // find length of rightNum
        for(int i = rightNumIndex; i < myList.size(); i++){
            string cur = myList[i];
            if(cur == "}"){
                break;
            }
            if(cur != "," && stoi(cur) == max){
                length++;
            }
        }

        // does 10 count as one space or two spaces!?!?!?!?!?
        int digits = 0;
        int number = stoi(myList[rightNumIndex]);
        while (number > 0) {
            number /= 10;
            digits++;
        }

        length *= digits;

        // finds left is there is one
        for(int i = 0; i < myList.size(); i++){
            string cur = myList[i];
        
            if(cur == "."){
                dotSize++;
            }
            else{
                dotSize = 0;
            }

            if(dotSize >= length){
                found = true;
                leftDotIndex = i - dotSize + 1;
                break;
            }
        }

        cout << "leftDotIndex: " << leftDotIndex << endl;
        cout << "rightNumIndex: " << rightNumIndex << endl;
        cout << "dotSize: " << dotSize << endl;
        cout << "length: " << length << endl;

        if(!found){
            max--;
            continue;
        }

        // for(string str : myList){
        // cout << str;
        // //cout << endl;
        // }
        // //cout << endl << "leftIndex: " << leftDotIndex << " rightIndex: " << rightNumIndex << " max: " << max << " dotSiz: " << dotSize << " Length: " << length << endl;
        // cout << endl;

        // swap found
        if(dotSize >= length && leftDotIndex < rightNumIndex){
            int displacment = 0;
            for(int i = 0; i < length; i++){
                string cur = myList[rightNumIndex+i];

                while(cur == "," || cur == "}" || cur == "{" || cur == "."){
                    displacment++;
                    cur = myList[rightNumIndex + i + displacment];
                }
                swap(myList[leftDotIndex+i], myList[rightNumIndex+displacment+i]);
                //cout << "swaped" << myList[leftDotIndex] << " and " << myList[rightNumIndex] << endl;
            }
        }
        leftDotIndex = -1;
        max--;
    }
    
    cout << "myList size: " << myList.size() << endl;
    // for(string str : myList){
    //     cout << str;
    //     //cout << endl;
    // }
    // cout << endl;

    // check sum

    long long sum = 0;
    counter = 0;

    for(int i = 0; i < myList.size(); i++){
        string cur = myList[i];
        if(cur != "," && cur != "}" && cur != "{" && cur != "."){
            sum += stoi(cur) * counter;
            counter++;
        }
        if(cur == "."){
            counter++;
        }
    }


    return sum;
}



int main(){
    vector<int> input;
    //ifstream file("test.txt"); 
    ifstream file("data.txt"); 

    if (!file.is_open()) {
        cout << "ERROR opening file";
        return -1;
    }

    string line;
    while (getline(file, line)) {
        for (char ch : line) {
            if (isdigit(ch)) { 
                input.push_back(ch - '0'); 
            }
        }
    }
    file.close();
    
    

    long long dis = adv2(input);
    cout << "dis " << dis << endl;

    return 1;
}