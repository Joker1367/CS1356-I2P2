#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(void){
	int n;
	vector<int> table;
	set< pair<int, int> > s;
	cin >> n;
	while(n--){
		string str;
		cin >> str;
		if(str == "push_back"){
			int num;
			cin >> num;
			table.push_back(num);
			s.insert({num, table.size()});
		} 
		else if(str == "pop_back"){
			if(!table.empty()){
				int num = table.back();
				auto itr = s.find({table.back(), table.size()});
				s.erase(itr);
				table.pop_back();
			}
		}
		else if(str == "find"){
			int index;
			cin >> index;
			if(index <= table.size()){
				cout << table[index - 1] << "\n";
			}
		}
		else if(str == "min"){
			if(!s.empty()){
				auto itr = s.begin();
				cout << itr->first << " " << itr->second << "\n";
			}
		}
		else if(str == "max"){
			if(!s.empty()){
				auto itr = s.end();
				itr--;
				cout << itr->first << " " << itr->second << "\n";
			}
		}
	}
	return 0;
}


