#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double EPS = 1e-10;

int nCase, cCase, D, H, B, L;

int cmp(double x) {
    if (fabs(x) < EPS) {
        return 0;
    }
    if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}

void input() {
    scanf("%d%d%d%d", &D, &H, &B, &L);
}

void solve() {
    int cnt = (B + (D - 1)) / D;
    double d = (double) B / cnt / 2.0;
    double l = (double) L / cnt / 2.0;

    double ll = 0.0, rr = 1000000.0, mid;
    while (rr - ll > EPS) {
        mid = (ll + rr) / 2.0;
        double t = sqrt(1 + 1.0 / 4.0 / mid / mid / d / d);
        double s = mid * d * d * t + 1.0 / 4.0 / mid * (log(2 * mid * d * (t + 1)));
        if (cmp(s - l) > 0) {
            rr = mid;
        } else {
            ll = mid;
        }
    }
    double ans = (double) H - mid * d * d;

    if (cCase) {
        printf("\n");
    }
    printf("Case %d:\n", ++cCase);
    printf("%.2lf\n", ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
