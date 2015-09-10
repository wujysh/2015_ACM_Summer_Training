#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 110;
const double EPS = 1e-12;
int dcnt, dx[9], dy[9], dz[9], n;
double step;

struct Team {
    double a, b, c;
    Team() {}
    Team(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
    Team operator - (const Team &t) const {
        return Team(a - t.a, b - t.b, c - t.c);
    }
    double len() {
        return sqrt(a * a + b * b + c * c);
    }
} team[MAXN];

void init() {
    dcnt = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                dx[dcnt] = i;
                dy[dcnt] = j;
                dz[dcnt] = k;
                dcnt++;
            }
        }
    }
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf", &team[i].a, &team[i].b, &team[i].c);
        step = max(step, max(team[i].a, max(team[i].b, team[i].c)));
    }
}

double calc(Team t) {
    double ret = 0;
    for (int i = 0; i < n; i++) {
        ret += (team[i] - t).len();
    }
    return ret;
}

void solve() {
    Team cur = Team(0, 0, 0);
    while (step > EPS) {
        double t = calc(cur);
        for (int i = 0; i < dcnt; i++) {
            Team nxt = Team(cur.a + step * dx[i], cur.b + step * dy[i], cur.c + step * dz[i]);
            double tt = calc(nxt);
            if (tt < t) {
                cur = nxt;
                t = tt;
            }
        }
        step *= 0.99;
    }
    printf("%.3f %.3f %.3f\n", cur.a, cur.b, cur.c);
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}
