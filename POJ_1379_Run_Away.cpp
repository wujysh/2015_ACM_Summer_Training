#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;

const int MAXN = 1010;
const int SEED = 20;  // number of seeds
const int INF = 1e50;
const int RAD = 1000;
const double EPS = 0.01;
int T, M;
double X, Y;

struct Point {
    double x, y, val;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y), val(0.0) {}
} hole[MAXN], seed[SEED];

void input() {
    scanf("%lf%lf%d", &X, &Y, &M);
    for (int i = 0; i < M; i++) {
        scanf("%lf%lf", &hole[i].x, &hole[i].y);
    }
}

double dis(Point a, Point b) {  // calculate the distance between two points
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double judge(Point t) {  // calculate the maximum distance between holes
    double len = INF;
    for (int i = 0; i < M; i++) {
        len = min(len, dis(t, hole[i]));
    }
    return len;
}

double rand_double() {  // generate a random double in (0, 1)
    return rand() % (RAD + 1) / (1.0 * RAD);
}

Point rand_point(Point a, Point b) {  // generate a random point in square(a, b)
    double x = a.x + (b.x - a.x) * rand_double();
    double y = a.y + (b.y - a.y) * rand_double();
    Point t = Point(x, y);
    t.val = judge(t);
    return t;
}

void solve() {
    seed[0] = Point(0, 0);
    seed[1] = Point(X, Y);
    seed[2] = Point(0, Y);
    seed[3] = Point(X, 0);
    for (int i = 4; i < SEED; i++) {
        seed[i] = rand_point(seed[0], seed[1]);
    }

    double step = max(X, Y);
    while (step > EPS) {
        for (int i = 0; i < SEED; i++) {
            for (int j = 0; j < SEED; j++) {
                Point t = rand_point(Point(max(0.0, seed[i].x-step), max(0.0, seed[i].y-step)), Point(min(X, seed[i].x+step), min(Y, seed[i].y+step)));
                if (t.val > seed[i].val) {
                    seed[i] = t;
                }
            }
        }
        step *= 0.9;
    }

    Point ans;
    for (int i = 0; i < SEED; i++) {
        if (seed[i].val > ans.val) {
            ans = seed[i];
        }
    }
    printf("The safest point is (%.1f, %.1f).\n", ans.x, ans.y);
}

int main() {
    //srand(time(NULL));
    scanf("%d", &T);
    while (T--) {
        input();
        solve();
    }
    return 0;
}
