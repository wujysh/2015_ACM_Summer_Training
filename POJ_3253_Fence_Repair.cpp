#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

int n;

int main() {
    while (scanf("%d", &n)) {
        priority_queue<long long, vector<long long>, greater<long long> > q;
        for (int i = 0; i < n; i++) {
            long long x;
            scanf("%lld", &x);
            q.push(x);
        }
        long long ans = 0;
        while (q.size() >= 2) {
            long long x = q.top();
            q.pop();
            long long y = q.top();
            q.pop();
            ans += x + y;
            q.push(x + y);
        }
        printf("%lld\n", ans);
        break;
    }
    return 0;
}
