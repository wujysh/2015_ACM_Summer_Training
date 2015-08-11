#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 210;
const int MOD = 1e9+7;

char str[MAXN];
long long f[MAXN];
int n;

void init() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i-1] * 2 % MOD;
    }
}

long long DP(int i) {
    if (i == n) return 0;
    if (str[i] == '0') {
        return (2 * DP(i+1)) % MOD;
    } else if (str[i] == '1') {
        return ((2 * DP(i+1)) % MOD + f[2*(n-i-1)]) % MOD;
    }
}

int main() {
    init();

    scanf("%s", str);
    n = strlen(str);

    printf("%I64d\n", DP(0));

    return 0;
}
