#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 3;
const double EPS = 1e-7;

inline int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    friend Point operator + (const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    friend bool operator == (const Point &a, const Point &b) {
        return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
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
    double norm() {
        return sqrt(sqr(x) + sqr(y));
    }
};
double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
double dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
double dist(const Point &a, const Point &b) {
    return (a - b).norm();
}
Point rotate_point(const Point &p, double A) {
    double tx = p.x, ty = p.y;
    return Point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}

Point p[MAXN];

bool input() {
    bool flag = false;
    for (int i = 0; i < 3; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        if (!flag && (p[i].x || p[i].y)) {
            flag = true;
        }
    }
    return flag;
}

void solve() {
    double angle[MAXN], len[MAXN], radius[MAXN];
    Point line[MAXN];

    for (int i = 0; i < 3; i++) {
        line[0] = p[(i+1) % 3] - p[i];
        line[1] = p[(i+2) % 3] - p[i];
        angle[i] = acos(dot(line[0], line[1]) / line[0].norm() / line[1].norm()) / 2.0;
        len[i] = dist(p[i], p[(i+1) % 3]);
    }

    double l = 0, r = min(len[0] * tan(angle[0]), len[2] * tan(angle[0])), mid;
    while (r - l > EPS) {
        mid = (l + r) / 2.0;

        double A, B, C;
        A = 1.0 / tan(angle[1]);
        B = 2 * sqrt(mid);
        C = mid / tan(angle[0]) - len[0];
        radius[0] = (sqrt(B * B - 4 * A * C) - B) / A / 2.0;
        radius[0] *= radius[0];

        A = 1.0 / tan(angle[2]);
        B = 2 * sqrt(mid);
        C = mid / tan(angle[0]) - len[2];
        radius[1] = (sqrt(B * B - 4 * A * C) - B) / A / 2.0;
        radius[1] *= radius[1];

        if (radius[0] / tan(angle[1]) + radius[1] / tan(angle[2]) + 2 * sqrt(radius[0] * radius[1]) - len[1] > 0) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.6lf %.6lf %.6lf\n", l, radius[0], radius[1]);
}

int main() {
    while (input()) {
        solve();
    }
    return 0;
}
