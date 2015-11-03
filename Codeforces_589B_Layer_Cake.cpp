#include <bits/stdc++.h>
using namespace std;

int n;
pair<int, int> p[4444];

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &p[i].first, &p[i].second);
            if (p[i].first > p[i].second) {
                swap(p[i].first, p[i].second);
            }
        }
        sort(p, p + n);
        multiset<int> s;
        multiset<int>::reverse_iterator it;
        s.insert(p[n - 1].second);
        int l, r;
        long long ans = 1LL * p[n - 1].first * p[n - 1].second;
        l = p[n - 1].first, r = p[n - 1].second;
        for (int i = n - 2; i >= 0; i--) {
            s.insert(p[i].second);
            int z = 0;
            for (it = s.rbegin(); it != s.rend(); it++) {
                z++;
                if (1LL * z * p[i].first * (*it) > ans) {
                    ans = 1LL * z * p[i].first * (*it);
                    l = p[i].first;
                    r = *it;
                }
            }
        }
        printf("%I64d\n%d %d\n", ans, l, r);
    }
    return 0;
}
