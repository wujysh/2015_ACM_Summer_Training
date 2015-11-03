#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 85;
const int MAXM = 200010;
const int MAXP = 20010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

typedef pair<double, double> Point;

Point operator - (const Point &a, const Point &b) {
    return Point(a.first - b.first, a.second - b.second);
}
Point operator * (const Point &a, double k) {
    return Point(a.first * k, a.second * k);
}
Point operator / (const Point &a, double k) {
    return Point(a.first / k, a.second / k);
}
bool zero(double x) {
    return fabs(x) < EPS;
}
bool operator == (const Point &a, const Point &b) {
    return zero(a.first - b.first) && zero(a.second - b.second);
}
double getAngle(const Point &a) {
    return atan2(a.second, a.first);
}
double det(const Point &a, const Point &b) {
    return a.first * b.second - a.second * b.first;
}

int edge[MAXM], prev[MAXM], mark[MAXM], tote, info[MAXP], N;
Point a[MAXN], b[MAXN];
vector<Point> p;

bool intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &res) {
    double k1 = det(b - a, c - a), k2 = det(b - a, d - a);
    if (zero(k1 - k2)) return false;
    res = (d * k1 - c * k2) / (k1 - k2);
    return true;
}

void addEdge(int x, int y) {
    edge[tote] = y;
    prev[tote] = info[x];
    info[x] = tote++;
    edge[tote] = x;
    prev[tote] = info[y];
    info[y] = tote++;
}

vector<double> divide() {
    vector<Point> p;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            Point res;
            if (intersect(a[i], b[i], a[j], b[j], res)) {
                p.push_back(res);
            }
        }
    }
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    memset(info, 0, sizeof(info));
    tote = 2;
    for (int i = 0; i < N; i++) {
        int last = -1;
        for (int j = 0; j < p.size(); j++) {
            if (zero(det(b[i] - a[i], p[j] - a[i]))) {
                if (last != -1) {
                    addEdge(last, j);
                }
                last = j;
            }
        }
    }

    memset(mark, 0, sizeof(mark));
    vector<double> area;
    for (int i = 2; i < tote; i++) {
        if (!mark[i]) {
            int laste = i ^ 1;
            int lastp = edge[i];
            int head = edge[laste];
            mark[i] = true;
            double ans;
            for (ans = det(p[head], p[lastp]); lastp != head; ) {
                double best = 1e20;
                int cur = -1;
                double base = getAngle(p[edge[laste]] - p[lastp]);
                for (int k = info[lastp]; k; k = prev[k]) {
                    if (k != laste) {
                        double tmp = getAngle(p[edge[k]] - p[lastp]) - base;
                        if (tmp < 0) {
                            tmp += PI * 2;
                        }
                        if (tmp >= PI * 2) {
                            tmp -= PI * 2;
                        }
                        if (tmp < best) {
                            best = tmp;
                            cur = k;
                        }
                    }
                }
                ans += det(p[lastp], p[edge[cur]]);
                lastp = edge[cur];
                laste = cur ^ 1;
                mark[cur] = true;
            }
            area.push_back(fabs(ans) * 0.5);
        }
    }

    sort(area.begin(), area.end());
    if (area.size()) {
        area.erase(area.end() - 1);
    }
    return area;
}

void input() {
    for (int i = 0; i < N; i++) {
        scanf("%lf%lf%lf%lf", &a[i].first, &a[i].second, &b[i].first, &b[i].second);
    }
}

void solve() {
    vector<double> area = divide();

    printf("%d\n", area.size());
    for (int i = 0; i < area.size(); i++) {
        printf("%.4lf\n", area[i]);
    }
}

int main() {
    while (~scanf("%d", &N)) {
        input();
        solve();
    }
    return 0;
}
