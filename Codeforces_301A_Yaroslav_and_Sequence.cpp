#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 210;
int n, a[MAXN], cnt, sum, mina;

int main() {
    scanf("%d", &n);

    cnt = sum = 0;
    mina = 1001;

    for (int i = 0; i < 2*n-1; i++) {
        scanf("%d", &a[i]);
        sum += abs(a[i]);
        mina = min(mina, (int)abs(a[i]));
        if (a[i] < 0) {
            cnt++;
        }
    }

    if (n % 2 == 1 || cnt % 2 == 0) {
        printf("%d\n", sum);
    } else {
        printf("%d\n", sum - 2 * mina);
    }

    return 0;
}
