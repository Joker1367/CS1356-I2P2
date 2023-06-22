#include <iostream>
#include <algorithm>
#include <string>

#define MAX_N 1000
#define MAX_BIT 5
#define MAX 100000

istream& operator>>(istream &in,  BigInt &b){
    string str; in >> str;
    if(str[0] == '-'){
        x.sign = -1;
        str = str.substr(1, str.size() - 1);
    }
    else x.sign  = 1;

    reverse(str.begin(), str.end());
    
}