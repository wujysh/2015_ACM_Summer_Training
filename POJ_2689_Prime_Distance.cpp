#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cmath>
using namespace std;

const int MAXN = 100010;

int L, U;

bool valid[MAXN];
int totPrime, prime[MAXN];
void getPrime(int n) {
    memset(valid, true, sizeof(valid));
    totPrime = 0;
    for (int i = 2; i <= n; i++) {
        if (valid[i]) {
            prime[++totPrime] = i;
        }
        for (int j = 1; j <= totPrime && i*prime[j] <= n; j++) {
            valid[i*prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

bool valid2[MAXN * 10];
int totPrime2, prime2[MAXN * 10];
void getPrime2(int L, int U) {
    memset(valid2, true, sizeof(valid2));
    if (L < 2) L = 2;
    for (int i = 1; i <= totPrime && (long long) prime[i] * prime[i] <= U; i++) {
        int s = L / prime[i] + (L % prime[i] > 0);
        if (s == 1) s = 2;
        for (int j = s; (long long) j * prime[i] <= U; j++) {
            if ((long long) j * prime[i] >= L) {
                valid2[j*prime[i] - L] = false;
            }
        }
    }
    totPrime2 = 0;
    for (int i = 0; i <= U-L; i++) {
        if (valid2[i]) {
            prime2[++totPrime2] = i + L;
        }
    }
}

void solve() {
    getPrime2(L, U);
    if (totPrime2 < 2) {
        printf("There are no adjacent primes.\n");
    } else {
        int c1 = 0, c2 = INT_MAX, d1 = 0, d2 = 0;
        for (int i = 1; i < totPrime2; i++) {
            if (prime2[i+1] - prime2[i] < c2 - c1) {
                c1 = prime2[i];
                c2 = prime2[i+1];
            }
            if (prime2[i+1] - prime2[i] > d2 - d1) {
                d1 = prime2[i];
                d2 = prime2[i+1];
            }
        }
        printf("%d,%d are closest, %d,%d are most distant.\n", c1, c2, d1, d2);
    }
}

int main() {
    getPrime(MAXN);
    while (~scanf("%d%d", &L, &U)) {
        solve();
    }
    return 0;
}

