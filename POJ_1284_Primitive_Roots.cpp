#include <iostream>
#include <cstdio>
using namespace std;

// 若p是一个素数，则p有φ(p-1)个原根

int phi(int x) {
    int ans = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            x /= i;
            ans *= i - 1;
            while (x % i == 0) {
                x /= i;
                ans *= i;
            }
        }
    }
    if (x > 1) {
        ans *= x - 1;
    }
    return ans;
}

int main() {
    int p;
    while (~scanf("%d", &p)) {
        printf("%d\n", phi(p - 1));
    }
    return 0;
}
