#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

long long a;

void solve() {
    queue<long long> q;
    q.push(1);

    while (!q.empty()) {
        long long cur = q.front();
        q.pop();

        if (cur % a == 0) {
            printf("%lld\n", cur);
            break;
        }

        for (int i = 0; i < 2; i++) {
            q.push(cur * 10 + i);
        }
    }
}

int main() {
    while (~scanf("%lld", &a) && a) {
        solve();
    }
    return 0;
}
