#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;

const int MAXN = 110;
const int SEED = 20;  // number of seeds
const int INF = 1e50;
const int RAD = 1000;
const double EPS = 0.01;
int T, N;
double X, Y;

struct Point {
    double x, y, val;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y), val(INF) {}
} computer[MAXN], seed[SEED];

void init() {
    X = Y = 0;
}

void input() {
    for (int i = 0; i < N; i++) {
        scanf("%lf%lf", &computer[i].x, &computer[i].y);
        X = max(X, computer[i].x);
        Y = max(Y, computer[i].y);
    }
}

double dis(Point a, Point b) {  // calculate the distance between two points
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double judge(Point t) {  // calculate the maximum distance between holes
    double len = 0;
    for (int i = 0; i < N; i++) {
        len += dis(t, computer[i]);
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
                if (t.val < seed[i].val) {
                    seed[i] = t;
                }
            }
        }
        step *= 0.9;
    }

    Point ans;
    for (int i = 0; i < SEED; i++) {
        if (seed[i].val < ans.val) {
            ans = seed[i];
        }
    }
    printf("%.0f\n", ans.val);
}

int main() {
    //srand(time(NULL));
    while (~scanf("%d", &N)) {
        init();
        input();
        solve();
    }
    return 0;
}
