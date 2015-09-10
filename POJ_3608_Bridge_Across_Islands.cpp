#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-10;

int N, M;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator + (const Point &p) {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point &p) {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double &d) {
        return Point(x * d, y * d);
    }
    bool operator < (const Point &a) const {
        if (x != a.x) return x < a.x;
        else return y < a.y;
    }
    double dot(const Point &p) {
        return x * p.x + y * p.y;
    }
    double det(const Point &p) {
        return x * p.y - y * p.x;
    }
} A[MAXN], B[MAXN];

inline double cross(Point A, Point B, Point C) {  // 向量 AB 与 AC 的叉积 如果叉积大于0，那么C在向量AB的逆时针方向，叉积小于0则在AB的顺时针方向。如果叉积等于0，则ABC共线。
    return (B - A).det(C - A);
}

inline double multi(Point A, Point B, Point C) {  // 向量 AB 与 AC 的点积 如果点积的结果为0，那么这两个向量互相垂直
    return (B - A).dot(C - A);
}

inline double dist(Point A, Point B) {  // 两点距离
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

inline void anticlockwise_sort(Point *p, int N) {  // 逆时针排序
    for (int i = 0; i < N - 2; ++i) {
        double tmp = cross(p[i], p[i + 1], p[i + 2]);
        if (tmp > EPS) return;
        else if (tmp < -EPS) {
            reverse(p, p + N);
            return;
        }
    }
}

inline double point_to_line(Point A, Point B, Point C) {  //计算C点到线段AB的最短距离
    if (dist(A, B) < EPS) return dist(B, C);
    if (multi(A, B, C) < -EPS) return dist(A, C);
    if (multi(B, A, C) < -EPS) return dist(B, C);
    return fabs(cross(A, B, C) / dist(A, B));
}

inline double line_to_line(Point A, Point B, Point C, Point D) {  //求一条线段的两端点到另外一条线段的距离，反过来一样，共4种情况
    return min(min(point_to_line(A, B, C), point_to_line(A, B, D)), min(point_to_line(C, D, A), point_to_line(C, D, B)));
}

void input() {
    for (int i = 0; i < N; i++) {
        scanf("%lf%lf", &A[i].x, &A[i].y);
    }
    for (int i = 0; i < M; i++) {
        scanf("%lf%lf", &B[i].x, &B[i].y);
    }
}

void solve() {
    anticlockwise_sort(A, N);
    anticlockwise_sort(B, N);

    int yminA = 0, ymaxB = 0;
    for (int i = 0; i < N; i++) {
        if (A[i].y < A[yminA].y) {
            yminA = i;  // A上y坐标最小的顶点
        }
    }
    for (int i = 0; i < M; i++) {
        if (B[i].y > B[ymaxB].y) {
            ymaxB = i;  // B上y坐标最大的顶点
        }
    }
    A[N] = A[0];
    B[M] = B[0];
    double arg, ans = INF;

    for (int i = 0; i < N; i++) {
        while (arg = cross(A[yminA + 1], B[ymaxB + 1], A[yminA]) - cross(A[yminA + 1], B[ymaxB], A[yminA]) > EPS) {
            ymaxB = (ymaxB + 1) % M;
        }
        if (fabs(arg) > EPS) {
            ans = min(ans, point_to_line(A[yminA], A[yminA + 1], B[ymaxB]));  // arg != 0 不平行
        } else {
            ans = min(ans, line_to_line(A[yminA], A[yminA + 1], B[ymaxB], B[ymaxB + 1]));  // arg = 0 平行
        }
        yminA = (yminA + 1) % N;
    }

    printf("%.5f\n", ans);
}

int main() {
    while (scanf("%d%d", &N, &M) && (N || M)) {
        input();
        solve();
    }
    return 0;
}
