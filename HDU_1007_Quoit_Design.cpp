#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 100010;
const double INF = 1e100;
const double EPS = 1e-8;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
} a[MAXN];

int n, s[MAXN];

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

bool cmpx(int i, int j) {
    return cmp(a[i].x - a[j].x) < 0;
}

bool cmpy(int i, int j) {
    return cmp(a[i].y - a[j].y) < 0;
}

double dis(int i, int j) {
    return sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
}

double min_dist(int s[], int l, int r) {  // Divide and conquer
    double ans = INF;
    if (r - l < 20) {
        for (int i = l; i < r; i++) {
            for (int j = i+1; j < r; j++) {
                ans = min(ans, dis(s[i], s[j]));
            }
        }
        return ans;
    }
    int tl, tr, mid = (l + r) / 2;
    ans = min(min_dist(s, l, mid), min_dist(s, mid, r));
    for (tl = l; a[s[tl]].x < a[s[mid]].x - ans; tl++);
    for (tr = r-1; a[s[tr]].x > a[s[mid]].x + ans; tr--);
    sort(s + tl, s + tr, cmpy);
    for (int i = tl; i < tr; i++) {
        for (int j = i+1; j < min(tr, i+6); j++) {
            ans = min(ans, dis(s[i], s[j]));
        }
    }
    sort(s + tl, s + tr, cmpx);
    return ans;
}

double Min_Dist(int s[], int n) {
    for (int i = 0; i < n; i++) {
        s[i] = i;
    }
    sort(s, s + n, cmpx);
    return min_dist(s, 0, n);
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &a[i].x, &a[i].y);
    }
}

void solve() {
    printf("%.2lf\n", Min_Dist(s, n) / 2.0);
}

int main() {
    while (~scanf("%d", &n) && n) {
        input();
        solve();
    }
    return 0;
}
