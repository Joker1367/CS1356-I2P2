#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void add(string a, string b);
void sub(string a, string b);

int main(void){
	string a, b;
	while(cin >> a >> b){
		add(a, b);
		sub(a, b);
	}
	return ;
}

void add(string a, string b){
	int a_size = a.length();
	int b_size = b.length();
	string s = "";
	if(b[0] == '-' && a[0] == '-'){
		int carry = 0;
		int sum;
		string res;
		int itr1 = a_size - 1;
		int itr2 = b_size - 1;
		while(itr1 >= 1 && itr2 >= 1){
			res = "0";
			sum = (carry + (a[itr1] + b[itr2] - '0' - '0')) % 10;
			carry = sum / 10;
			res[0] += sum;
			s = res + s;
			itr1--;
			itr2--;
		}
		if(itr1 > 0){
			while(itr1 > 0){
				res = "0";
				sum = (carry + (a[itr1] - '0')) % 10;
				carry = sum / 10;
				res[0] += sum;
				s = res + s;
				itr1--;
			}
			
		}
	}
	else if(b[0] == '-'){
		
	}
	else if(a[0] == '-'){
		
	}
	else{
		
	}
}


