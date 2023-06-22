#include <iostream>

#define MAX 1000000000000000000 // 10^18
#define MAXI 1000000000

using namespace std;

long long int fp(int pow){
    long long int res = 1;
    long long int factor = 2;
    while(pow > 0){
        if(pow % 2 == 1) res *= factor;
        factor *= factor;
        pow /= 2;
    }
    return res;
}

long long int find_k(int i, long long int num){
    long long int fps = fp(i);
    long long int l = 1; long long int r = MAX + 1;
    while(l < r){
        long long int mid = (r - l) / 2 + l;
        if(num / mid + 1 - fps + 1 < (mid - 1) / 2){
            r = mid;
            continue;
        }
        long long int tmp = mid * (fps - 1) + mid * (mid - 1) / 2;
        //cout << tmp << "\n";
        if(num == tmp) return mid;
        else if(num > tmp) l = mid + 1;
        else r = mid;
    }
    if(num / l + 1 - fps + 1 < (l - 1) / 2) return -1;
    long long int tmp = l * (fps - 1) + l * (l - 1) / 2;
    if(num == tmp) return l;
    else return -1;
}

int main(void){
    int t; cin >> t;
    while(t--){
        long long int num; cin >> num;
        long long int res = -1;
        for(int i = 0; i <= 63; i++){
            long long int k = find_k(i, num);
            if(k == -1) continue;
            else{
                //cout << i << " " << k << "\n";
                res = (res == -1) ? fp(i) * k : min(res, fp(i) * k);
            }
        }
        cout << res << "\n";
    }
    return 0;
}