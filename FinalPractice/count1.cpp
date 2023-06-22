#include <iostream>
#include <stdio.h>

using namespace std;

int count[1000001] = {0};

int main(void){
    //std::ios_base::sync_with_stdio(false);
    //cin.tie(0);
    for(int i = 1; i <= 1000000; i++){
        int tmp = i; count[i] += count[i - 1];
        while(tmp > 0){
            if(tmp % 10 == 1) count[i]++;
            tmp /= 10;
        }
    }
    int t; cin >> t;
    while(t--){
        int a, b; scanf("%d %d", &a, &b);
        printf("%d\n", count[b] - count[a - 1]);
    }
    return 0;
}