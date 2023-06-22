#include<iostream>
#include<stdio.h>
#include<string.h>
#include<set>

using namespace std;

int main(void){
    int n;
    int i, j;
    set<int> s;

    cin >> n;

    while(n != 0){
        string str;
        cin >> str;
        if(str == "print"){
            if(!s.empty()){
                int i = 1;
                for(auto itr: s){
                    if(i == s.size()){
                        cout << itr << endl;
                    }
                    else{
                        cout << itr << " ";
                    }
                    i++;
                }
            }
        }
        else if(str == "insert"){
            cin >> i;
            s.insert(i);
        }
        else if(str == "min"){
            if(!s.empty()){
                auto itr = s.begin();
                cout << (*itr) << "\n";
            }
        }
        else if(str == "range_erase"){
            cin >> i >> j;
            if(!s.empty()){
                auto itr1 = s.lower_bound(i);
                auto itr2 = s.upper_bound(j);
                s.erase(itr1, itr2);
            }
        }
        n--;
    }
    return 0;
}