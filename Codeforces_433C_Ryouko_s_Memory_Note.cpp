#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100010;

int n, m, a[MAXN];
vector<int> v[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }

    long long sum = 0;
    for (int i = 1; i <= m; i++) {
        if (i > 1) {
            if (a[i-1] != a[i]) {
                v[a[i]].push_back(a[i-1]);
            }
            sum += abs(a[i] - a[i-1]);
        }
        if (i < m) {
            if (a[i+1] != a[i]) {
                v[a[i]].push_back(a[i+1]);
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i].empty()) continue;
        sort(v[i].begin(), v[i].end());
        int m = v[i][(int)v[i].size() / 2];

        long long t = 0;
        for (int j = 0; j < v[i].size(); j++) {
            t += abs(i - v[i][j]) - abs(m - v[i][j]);
        }
        ans = max(ans, t);
    }

    ans = sum - ans;
    printf("%I64d\n", ans);

    return 0;
}
