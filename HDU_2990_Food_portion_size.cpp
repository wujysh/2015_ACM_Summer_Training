#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;

int a, b, n, y[MAXN], ans1, ans2;

void init() {
    ans1 = INF, ans2 = 1;
}

void input() {
    scanf("%d%d", &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &y[i]);
    }
}

void solve() {
    for (int k = 1; k <= 3; k++) {
        for (int i = 1; i <= n; i++) {
            bool flag = true;
            int cost = 0;
            for (int j = 1; j <= n; j++) {
                int time = (y[j] * k + y[i]-1) / y[i];
                //cout << fetch << endl;
                if (time > 3) {
                    flag = false;
                    break;
                }
                cost += a * (time * y[i] - y[j] * k) + b * time * k;  // k * cost
            }

            if (flag && cost * ans2 < ans1 * k) {
                ans1 = cost;
                ans2 = k;
            }
        }
    }

    if (ans1 % ans2 == 0) {
        printf("%d\n", ans1 / ans2);
    } else {
        printf("%d / %d\n", ans1, ans2);
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        input();
        solve();
    }
    return 0;
}
