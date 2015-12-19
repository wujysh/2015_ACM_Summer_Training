#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 25;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-10;

double v, b, g, min_x, max_x, max_y;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
};

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

bool point_on_segment(Point p, Point s, Point t) {
    return cmp(det(p-s, t-s)) == 0 && cmp(dot(p-s, p-t)) <= 0;
}

struct Polygon {
    int n;
    Point a[MAXN];
    Polygon() {}
    int point_in(Point t) {  // 0-out, 1-in, 2-on
        int num = 0;
        a[n] = a[0];
        for (int i = 0; i < n; i++) {
            if (point_on_segment(t, a[i], a[i+1])) return 2;
            int k = cmp(det(a[i+1]-a[i], t-a[i]));
            int d1 = cmp(a[i].y - t.y);
            int d2 = cmp(a[i+1].y - t.y);
            if (k > 0 && d1 <= 0 && d2 > 0) num++;
            if (k < 0 && d2 <= 0 && d1 > 0) num--;
        }
        return num != 0;
    }
} p;

void init() {
    max_x = max_y = -INF;
    min_x = INF;
}

void input() {
    scanf("%d", &p.n);
    for (int i = 0; i < p.n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        p.a[i] = Point(x, y);
        max_x = max(max_x, x);
        min_x = min(min_x, x);
        max_y = max(max_y, y);
    }
}

void solve() {
    double step = 0.001, max_t;
    if (cmp(g) != 0) {
        max_t = 2.0 * b / g;
    } else {
        max_t = max_y / b;
    }
    for (double t = 0.0; t < max_t + 1; t += step) {
        if (p.point_in(Point(-v*t, b*t - 0.5*g*t*t)) == 1) {
            printf("%.2f\n", t);
            return;
        }
        if (v > 0) {
            if (-v*t < min_x) break;
        } else if (v < 0) {
            if (-v*t > max_x) break;
        }
    }

    printf("Miss!\n");
}

int main() {
    while (~scanf("%lf%lf%lf", &v, &b, &g) && (v || b || g)) {
        init();
        input();
        solve();
    }
    return 0;
}
