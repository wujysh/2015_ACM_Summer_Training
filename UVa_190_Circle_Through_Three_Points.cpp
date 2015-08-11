#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

void solve(double x1, double y1, double x2, double y2, double x3, double y3) {
    double A1 = x2 - x1, B1 = y2 - y1, C1 = x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1;
    double A2 = x3 - x1, B2 = y3 - y1, C2 = x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1;
    double c = (B1 * C2 - B2 * C1) / (A1 * B2 - A2 * B1);
    double d = (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);  // 解方程
    double e = -x2 * x2 - y2 * y2 - x2 * c - y2 * d;
    double h = c / -2.0, k = d / -2.0;  // 圆心坐标
    double r = hypot(x2 - h, y2 - k);  // 计算距离
    // hypot: 对于给定的直角三角形的两个直角边，求其斜边的长度。

    printf("(x ");
    if (h > 0) {
        printf("- %.3lf)^2 + (y ", h);
    } else {
        printf("+ %.3lf)^2 + (y ", -h);
    }
    if (k > 0) {
        printf("- %.3lf)^2 = %.3lf^2\n", k, r);
    } else {
        printf("+ %.3lf)^2 = %.3lf^2\n", -k, r);
    }

    printf("x^2 + y^2 ");
    if (c > 0) {
        printf("+ %.3lfx ", c);
    } else {
        printf("- %.3lfx ", -c);
    }
    if (d > 0) {
        printf("+ %.3lfy ", d);
    } else {
        printf("- %.3lfy ", -d);
    }
    if (e > 0) {
        printf("+ %.3lf = 0\n\n", e);
    } else {
        printf("- %.3lf = 0\n\n", -e);
    }
}

int main() {
    double x0, y0, x1, y1, x2, y2;
    while (~scanf("%lf%lf%lf%lf%lf%lf", &x0, &y0, &x1, &y1, &x2, &y2)) {
        solve(x0, y0, x1, y1, x2, y2);
    }
    return 0;
}
