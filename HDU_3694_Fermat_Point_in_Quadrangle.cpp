#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double INF = 1e10;
const double EPS = 1e-8;

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    friend Point operator * (const Point &a, const double &b) {
        return Point(a.x * b, a.y * b);
    }
    friend Point operator * (const double &a, const Point &b) {
        return Point(a * b.x, a * b.y);
    }
    friend Point operator / (const Point &a, const double &b) {
        return Point(a.x / b, a.y / b);
    }
    bool operator < (const Point &b) const {
        if (cmp(y * b.x - b.y * x) == 0) {
            return x * x + y * y < b.x * b.x + b.y * b.y;
        }
        return y * b.x < b.y * x;
    }
} p[5];

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Point a, b;
    Line() {}
    Line(Point _a, Point _b) : a(_a), b(_b) {}
};

double ans;

void init() {
    ans = INF;
}

void input() {
    for (int i = 1; i < 4; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
}

void line_make_point(Line a, Line b, Point &res) {
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    res = (s1 * a.b - s2 * a.a) / (s1 - s2);
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void solve() {
    for (int i = 1; i < 4; i++) {
        p[i] = p[i] - p[0];
    }
    p[0].x = 0;
    p[0].y = 0;

    sort(p, p + 4);

    line_make_point(Line(p[0], p[2]), Line(p[1], p[3]), p[4]);

    for (int i = 0; i < 5; i++) {
        double dis = 0.0;
        for (int j = 0; j < 4; j++) {
            dis += dist(p[j], p[i]);
        }
        if (dis < ans) {
            ans = dis;
        }
    }

    printf("%.4f\n", ans);
}

int main() {
    while (~scanf("%lf%lf", &p[0].x, &p[0].y)) {
        init();
        input();
        if (p[0].x == -1 && p[0].y == -1 && p[1].x == -1 && p[1].y == -1 && p[2].x == -1 && p[2].y == -1 && p[3].x == -1 && p[3].y == -1) break;
        solve();
    }
    return 0;
}
