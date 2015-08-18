#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 100010;

int n, nCase, a[MAXN];
long long sum[MAXN], ans, cnt, l2[40];

void init() {
    ans = 0;
//    l2[0] = 1;
//    for (int i = 1; i <= 35; i++) {
//        l2[i] = l2[i-1] * 2;
//    }
}

void input() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

inline int log_2(long long x) {
//    if (x == 0) {
//        return 0;
//    } else {
//        int cnt = 0;
//        while (x > 1) {
//            x = x / 2;
//            cnt++;
//        }
//        return cnt;
//    }
    return x == 0 ? 0 : floor(log2(x));
}

long long x;
bool cmp(long long a, long long b) {
    return log_2(a - x) <= log_2(b - x);
}

int binary(int ll, int rr, long long x) {
    int l = ll, r = rr, mid;
    while (l < r) {
        cnt++;
        mid = (l + r) >> 1;
        if (cmp(sum[mid], x)) {  // sum[mid] <= x
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return r;
}

void solve() {
    sum[0] = 0;
    vector<int> v;
    v.push_back(1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + a[i];
        if (log_2(sum[i]) > log_2(sum[i-1])) {
            v.push_back(i);
        }
    }
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        x = sum[i-1];

        if (i == 1) {
            for (int j = 1; j < v.size(); j++) {
                //cout << v[j] << endl;
                ans += (i+v[j-1] + i+v[j]-1) * (long long) log_2(sum[v[j-1]]-x) * (v[j]-1-v[j-1]+1) / 2;
            }
        } else {
            int l = i;
            while (l <= n) {
                int index;
                if (log_2(sum[l]-x) >= log_2(sum[n]-x)) {
                    index = n;
                } else {
                    index = binary(l, n, sum[l]) - 1;
                    //index = upper_bound(sum+l, sum+n, sum[l], cmp) - sum - 1;
                }
                ans += (i+l + i+index) * (long long) log_2(sum[l]-x) * (index-l+1) / 2;
                l = index + 1;
            }
        }

        int l = i;
        while (l <= n) {
            //cnt++;
            int index;
            if (log_2(sum[l]-x) >= log_2(sum[n]-x)) {
                index = n;
            } else {
                index = binary(l, n, sum[l]) - 1;
                //index = upper_bound(sum+l, sum+n, sum[l], cmp) - sum - 1;
            }
            ans += (i+l + i+index) * (long long) log_2(sum[l]-x) * (index-l+1) / 2;
            l = index + 1;
        }
        //ans += (long long) (n-i+1) * (2*i + n + i) / 2;
    }
    ans += ((long long) n * n * n + 2 * (long long) n * n + n) / 2;
    cout << cnt << endl;
    printf("%lld\n", ans);
}

int main() {
    freopen("test.in", "r", stdin);
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
