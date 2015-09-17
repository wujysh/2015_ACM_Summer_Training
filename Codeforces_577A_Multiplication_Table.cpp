#include <iostream>
#include <cstdio>
using namespace std;

int n, x;

int main() {
    while (~scanf("%d%d", &n, &x)) {
        int ans = 0;
        for (int i = (x + n-1) / n; i <= min(n, x); i++) {
            if (x % i == 0) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
