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

// have a count and ++ for each correct step
// when you hit a num count num and count++
// when time for num stop counting until ,
// add all to string then string to int
// same for next num but stop counting at )
// if total count is 8 then add (int1 * int2) to a sum

int adv(string data){
    int sum = 0;
    int count = 0;
    
    string stringNumOne;
    string stringNumTwo;

    int NumOne = 0;
    int NumTwo = 0;

    bool doIt = true;
    int doitCount = 0;
    int dontDoitCount = 0;

    for(char c : data){

        if(c == 'd' && dontDoitCount == 0){
            dontDoitCount++;
        }
        else if(c == 'o' && dontDoitCount == 1){
            dontDoitCount++;
        }
        else if(c == 'n' && dontDoitCount == 2){
            dontDoitCount++;
        }
        else if(c == '\'' && dontDoitCount == 3){
            dontDoitCount++;
        }
        else if(c == 't' && dontDoitCount == 4){
            dontDoitCount++;
        }
        else if(c == '(' && dontDoitCount == 5){
            dontDoitCount++;
        }
        else if(c == ')' && dontDoitCount == 6){
            doIt = false;
            dontDoitCount = 0;
        }
        else{
            dontDoitCount = 0;
        }



        if(c == 'd' && doitCount == 0){
            doitCount++;
        }
        else if(c == 'o' && doitCount == 1){
            doitCount++;
        }
        else if(c == '(' && doitCount == 2){
            doitCount++;
        }
        else if(c == ')' && doitCount == 3){
            doIt = true;
            doitCount = 0;
        }
        else{
            doitCount = 0;
        }




        if(c == 'm'){
            count++;
        }
        else if(c == 'u' && count == 1){
            count++;
        }
        else if(c == 'l' && count == 2){
            count++;
        }
        else if(c == '(' && count == 3){
            count++;
        }
        else if( isdigit(c) && count == 4){
            // start counting digits
            count++;
            stringNumOne.push_back(c);
        }
        else if(isdigit(c) && count == 5 && c != ','){
            stringNumOne.push_back(c);
        }
        else if(c == ',' && count == 5){
            NumOne = stoi(stringNumOne);
            count++;
        }
        else if(isdigit(c) && count == 6 && c != ')'){
            stringNumTwo.push_back(c);
        }
        else if(c == ')' && count == 6 && doIt){
            NumTwo = stoi(stringNumTwo);
            count++;
            sum += (NumOne * NumTwo);

            count = 0;
            NumOne = 0;
            NumTwo = 0;
            stringNumOne = "";
            stringNumTwo = "";
        }
        else{
            count = 0;
            NumOne = 0;
            NumTwo = 0;
            stringNumOne = "";
            stringNumTwo = "";
        }
    }
    return sum;
}




int main(){
    std::ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << inputFile.rdbuf();  
    std::string input = buffer.str();
    inputFile.close();

    //int dis = adv("xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))");
    int dis = adv(input);
    cout << "dis " << dis << endl;

}