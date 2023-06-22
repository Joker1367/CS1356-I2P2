#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(void){
    int n;
    cin >> n;

    map< int, map< char, vector<string> > > bucket;
    while(n--){
        string str;
        int vowel = 0; char last = '\0';
        cin >> str;
        for(int i = 0; i < str.size(); i++){
            if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'){
                vowel++;
                last = str[i];
            }
        }
        bucket[vowel][last].push_back(str);
    }
    int comp = 0; int uncomp = 0;
    for(auto itr: bucket){
        auto map_ = itr.second;
        int tmp_comp = 0; int tmp_uncomp = 0;
        for(auto itr: map_){
            tmp_comp += itr.second.size() / 2;
            tmp_uncomp += itr.second.size();
        }
        comp += tmp_comp;
        uncomp += (tmp_uncomp - tmp_comp * 2) / 2;
    }
    if(comp <= uncomp){
        cout << comp << "\n";
    }
    else{
        cout << (comp + uncomp) / 2 << "\n";
    }
    return 0;
}