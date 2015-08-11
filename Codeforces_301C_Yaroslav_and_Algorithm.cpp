#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 110;
int n, a[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    //if (n >= 23) {
        for (int i = 0; i <= 8; i++) {
            printf("%d??<>%d\n", i, i+1);
        }
        printf("9??>>??0\n");
        printf("??<>1\n");
        for (int i = 0; i <= 9; i++) {
            printf("?%d>>%d?\n", i, i);
        }
        printf("?>>??\n");
        printf(">>?\n");
    //} else {
    //    sort(a, a+n);
    //    for (int i = n-1; i >= 0; i--) {
    //        printf("%d<>%d\n", a[i], a[i]+1);
    //    }
    //}
    return 0;
}
