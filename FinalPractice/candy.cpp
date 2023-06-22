#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void){
    int t; cin >> t;
    while(t--){
        vector<int> rgb;
        int r, g, b; cin >> r >> g >> b;
        int res = 0;
        rgb.push_back(r);
        rgb.push_back(g);
        rgb.push_back(b);
        sort(rgb.begin(), rgb.end());
        if(rgb[0] <= rgb[2] - rgb[1]){
            cout << rgb[0] + rgb[1] << "\n";
        }
        else{
            int res = 0;
            res += rgb[2] - rgb[1]; rgb[0] -= res; rgb[2] -= res;
            res += (rgb[0] / 2) * 2 + rgb[2] - rgb[0] / 2;
            cout << res << "\n";
        }
    }
    return 0;
}