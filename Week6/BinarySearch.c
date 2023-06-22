#include <stdio.h>
#include <stdlib.h>

int main(){
    int len, amt;
    int i;
    while(scanf("%d %d", &len, &amt) != EOF){
        int* arr = (int*)malloc(len * sizeof(int));
        for(i = 0; i < len; i++){
            scanf("%d", &arr[i]);
        }

        int num;
        while(amt--){
            scanf("%d", &num);
            int left = 0;
            int right = len - 1;
            int find = 0;
            while(left <= right){
                int mid = left + (right - left) / 2;
                if(arr[mid] == num){
                    printf("%d\n", mid + 1);
                    find = 1;
                    break;
                }
                else if(arr[mid] > num){
                    right = mid - 1;
                }
                else{
                    left = mid + 1;
                }
            }

            if(!find){
                printf("Break your bridge!\n");
            }
        }

        free(arr);
    }

    return 0;
}