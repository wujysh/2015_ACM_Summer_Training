#include <algorithm>
#include <iostream>
#include <complex>
#include <cstdio>
#include <vector>
#include <deque>
using namespace std;

const double EPS = 1e-10;
const double INF = 10000;

typedef complex<double> Point;
typedef pair<Point, Point> Halfplane;
typedef pair<Point, Point> Line;
typedef vector<Point> Convex;

inline int sgn(double n) {
    return fabs(n) < EPS ? 0 : (n < 0 ? -1 : 1);
}

inline double cross(Point a, Point b) {
    return (conj(a) * b).imag();
}

inline double dot(Point a, Point b) {
    return (conj(a) * b).real();
}

inline double satisfy(Point a, Halfplane p) {
    return sgn(cross(a - p.first, p.second - p.first)) <= 0;
}

Point crosspoint(const Halfplane &a, const Halfplane &b) {
    double k = cross(b.first - b.second, a.first - b.second);
    k = k / (k - cross(b.first - b.second, a.second - b.second));
    return a.first + (a.second - a.first) * k;
}

bool cmp(const Halfplane &a, const Halfplane &b) {
    int res = sgn(arg(a.second - a.first) - arg(b.second - b.first));
    return res == 0 ? satisfy(a.first, b) : res < 0;
}

vector<Point> halfplaneIntersection(vector<Halfplane> v) {
    sort(v.begin(), v.end(), cmp);
    deque<Halfplane> q;
    deque<Point> ans;
    q.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (sgn(arg(v[i].second - v[i].first) - arg(v[i-1].second - v[i-1].first)) == 0) {
            continue;
        }
        while (!ans.empty() && !satisfy(ans.back(), v[i])) {
            ans.pop_back();
            q.pop_back();
        }
        while (!ans.empty() && !satisfy(ans.front(), v[i])) {
            ans.pop_front();
            q.pop_front();
        }
        ans.push_back(crosspoint(q.back(), v[i]));
        q.push_back(v[i]);
    }
    while (!ans.empty() && !satisfy(ans.back(), q.front())) {
        ans.pop_back();
        q.pop_back();
    }
    while (!ans.empty() && !satisfy(ans.front(), q.back())) {
        ans.pop_front();
        q.pop_front();
    }
    ans.push_back(crosspoint(q.back(), q.front()));
    return vector<Point>(ans.begin(), ans.end());
}

Convex convexIntersection(Convex v1, Convex v2) {
    vector<Halfplane> h;
    for (int i = 0; i < v1.size(); i++) {
        h.push_back(Halfplane(v1[i], v1[(i+1) % v1.size()]));
    }
    for (int i = 0; i < v2.size(); i++) {
        h.push_back(Halfplane(v2[i], v2[(i+1) % v2.size()]));
    }
    return halfplaneIntersection(h);
}

bool comp_less(const Point &a, const Point &b) {
    return sgn(a.real() - b.real()) < 0 || sgn(a.real() - b.real()) == 0 && sgn(a.imag() - b.imag()) < 0;
}

Convex convex_hull(Convex a) {
    Convex res(2 * a.size() + 5);
    sort(a.begin(), a.end(), comp_less);
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = 0;
    for (int i = 0; i < a.size(); i++) {
        while (m > 1 && sgn(cross(res[m-1]-res[m-2], a[i]-res[m-2])) <= 0) {
            m--;
        }
        res[m++] = a[i];
    }
    int k = m;
    for (int i = a.size() - 2; i >= 0; i--) {
        while (m > k && sgn(cross(res[m-1]-res[m-2], a[i]-res[m-2])) <= 0) {
            m--;
        }
        res[m++] = a[i];
    }
    res.resize(m);
    if (a.size() > 1) {
        res.resize(m-1);
    }
    return res;
}

double area(Convex a) {
    double sum = 0;
    a.push_back(a[0]);
    for (int i = 0; i < a.size() - 1; i++) {
        sum += cross(a[i], a[i+1]);
    }
    return sum / 2.0;
}

int n, m;
Convex c1, c2;

void init() {
    c1.clear();
    c2.clear();
}

void input() {
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        c1.push_back(Point(x, y));
    }
    for (int i = 0; i < m; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        c2.push_back(Point(x, y));
    }
}

void solve() {
    c1 = convex_hull(c1);
    c2 = convex_hull(c2);
    double area1 = area(c1), area2 = area(c2);

    if (area1 == 0) {
        area1 = sqrt((c1[n-1] - c1[0]).real() * (c1[n-1] - c1[0]).real() + (c1[n-1] - c1[0]).imag() * (c1[n-1] - c1[0]).imag());
    }
    if (area2 == 0) {
        area2 = sqrt((c2[m-1] - c2[0]).real() * (c2[m-1] - c2[0]).real() + (c2[m-1] - c2[0]).imag() * (c2[m-1] - c2[0]).imag());
    }
    //cout << area2 << endl;

    printf("%.3lf\n", area(convexIntersection(c1, c2)) / area2);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        input();
        solve();
    }
    return 0;
}
