#include <iostream>
#include <set>

using namespace std;

int main(void){
    int n; cin >> n;
    set<pair<int, string>> s;
    while(n--){
        string str; cin >> str;
        if(str == "born"){
            string name; int age;
            cin >> name >> age;
            s.insert({age, name});
        }
        else if(str == "find"){
            string name; int age;
            cin >> name >> age;
            if(s.find({age, name}) != s.end()) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        }
        else if(str == "kill"){
            string name; int age;
            cin >> name >> age;
            s.erase({age, name});
        }
        else if(str == "young"){
            auto itr = s.begin();
            cout << itr->second << " " << itr->first << "\n";
        }
    }
    return 0;
}