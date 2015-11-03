#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 50010;
const long long INF = 0x3f3f3f3f3f3f3f3f;

int n, a, b, p[MAXN], d[MAXN];
long long w, wa, wb, va1, va2, vb1, vb2;
vector<long long> pa, pb;

void init() {
    pa.clear();
    pb.clear();
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    scanf("%lld%lld%lld%lld%lld%lld%lld", &w, &va1, &va2, &wa, &vb1, &vb2, &wb);
}

void solve() {
    swap(va1, vb1);
    swap(va2, vb2);
    long long ta = -a * (va1 + va2);
    long long tb = b * (vb1 + vb2);
    for (int i = 0; i < n; i++) {
        if (p[i] < 0) {
            if (d[i] == -1) {
                pa.push_back(ta + va2 * -p[i]);
                w += wa;
            } else if (d[i] == 1) {
                pa.push_back(ta - va1 * -p[i]);
            }
        } else if (p[i] > 0) {
            if (d[i] == 1) {
                pb.push_back(tb + vb2 * p[i]);
                w += wb;
            } else if (d[i] == -1) {
                pb.push_back(tb - vb1 * p[i]);
            }
        }
    }

    long long l = 0, r = INF;
    while (l < r) {
        long long m = (l + r) / 2;
        long long ww = w;
        for (int i = 0; ww > 0 && i < pa.size(); i++) {
            ww -= (m + pa[i]) / ta * wa;
        }
        for (int i = 0; ww > 0 && i < pb.size(); i++) {
            ww -= (m + pb[i]) / tb * wb;
        }
        if (ww <= 0) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    long long m = r;
    double ansa = 0.0, ansb = 0.0;
    bool fa = false, fb = false;
    for (int i = 0; i < pa.size(); i++) {
        long long ww = (m + pa[i]) / ta * wa;
        if ((m + pa[i]) % ta == 0) {
            ww -= wa;
            fa = true;
        }
        w -= ww;
        ansa += ww;
    }
    for (int i = 0; i < pb.size(); i++) {
        long long ww = (m + pb[i]) / tb * wb;
        if ((m + pb[i]) % tb == 0) {
            ww -= wb;
            fb = true;
        }
        w -= ww;
        ansb += ww;
    }
    if (fa && fb) {
        if (wa * 2 < w) {
            ansa += wa;
            ansb += w - wa;
        } else if (wb * 2 < w) {
            ansa += w - wb;
            ansb += wb;
        } else {
            ansa += w / 2.0;
            ansb += w / 2.0;
        }
    } else if (fa) {
        ansa += w;
    } else if (fb) {
        ansb += w;
    }

    printf("%.1lf %.1lf\n", ansa, ansb);
}

int main() {
    while (~scanf("%d%d%d", &n, &a, &b)) {
        init();
        input();
        solve();
    }
    return 0;
}
