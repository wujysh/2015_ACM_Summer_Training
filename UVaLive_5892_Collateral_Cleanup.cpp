#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>
#include <set>
using namespace std;

const int MAXN = 1000010;
const double INF = 1 << 30;
const double eps = 1e-8;

int cmp(double x) {
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct cmp_key {
    bool operator () (const double &k1, const double &k2) const {
        //return k2 - k1 > eps;
        return cmp(k1 - k2) < 0;
    }
};

int nCase, n, inDegree[MAXN];
bool visited[MAXN];
map<double, map<double, pair<set<int>, set<int> >, cmp_key>, cmp_key> mp;
vector<int> G[MAXN];
queue<int> q;

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Triangle {
    Point p[3];
    Triangle() {}
} triangle[MAXN];

void init() {
    mp.clear();
    for (int i = 0; i < MAXN; i++) {
        G[i].clear();
    }
    while (!q.empty()) {
        q.pop();
    }
    memset(inDegree, 0, sizeof(inDegree));
    memset(visited, false, sizeof(visited));
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d%d", &triangle[i].p[j].x, &triangle[i].p[j].y);
        }
    }
}

double det(Point a, Point b, Point c) {  // ab x ac
    double x1 = b.x - a.x;
    double y1 = b.y - a.y;
    double x2 = c.x - a.x;
    double y2 = c.y - a.y;
    return x1 * y2 - x2 * y1;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            double dx = triangle[i].p[(j + 1) % 3].x - triangle[i].p[j].x, dy = triangle[i].p[(j + 1) % 3].y - triangle[i].p[j].y, k, b, dir;
            if (dx == 0) {
                k = INF;
                continue;
            }
            if (dy == 0) {
                k = 0;
            } else {
                k = dy / dx;
            }
            b = triangle[i].p[j].y - k * triangle[i].p[j].x;
            dir = det(triangle[i].p[j], triangle[i].p[(j + 1) % 3], triangle[i].p[(j + 2) % 3]);
            if (k > 0) {
                if (dy < 0) {
                    if (dir > 0) {
                        mp[k][b].second.insert(i);
                    } else {
                        mp[k][b].first.insert(i);
                    }
                } else {
                    if (dir > 0) {
                        mp[k][b].first.insert(i);
                    } else {
                        mp[k][b].second.insert(i);
                    }
                }
            } else if (k < 0) {
                if (dy < 0) {
                    if (dir > 0) {
                        mp[k][b].first.insert(i);
                    } else {
                        mp[k][b].second.insert(i);
                    }
                } else {
                    if (dir > 0) {
                        mp[k][b].second.insert(i);
                    } else {
                        mp[k][b].first.insert(i);
                    }
                }
            } else if (cmp(k) == 0) {
                if (triangle[i].p[(j + 2) % 3].y - triangle[i].p[j].y < 0) {
                    mp[k][b].second.insert(i);
                } else {
                    mp[k][b].first.insert(i);
                }
            }
        }
    }

//    for (map<double, map<double, pair<set<int>, set<int> >, cmp_key>, cmp_key>::iterator it = mp.begin(); it != mp.end(); it++) {
//        for (map<double, pair<set<int>, set<int> >, cmp_key>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
//            printf("k = %.10lf, b = %.10lf\n", it->first, it2->first);
//
//            printf("UP: \n");
//            set<int> up = it2->second.first;
//            for (set<int>::iterator it1 = up.begin(); it1 != up.end(); it1++) {
//                printf("%d ", *it1);
//            }
//            printf("\n");
//
//            printf("DOWN: \n");
//            set<int> down = it2->second.second;
//            for (set<int>::iterator it1 = down.begin(); it1 != down.end(); it1++) {
//                printf("%d ", *it1);
//            }
//            printf("\n");
//        }
//    }

    for (map<double, map<double, pair<set<int>, set<int> >, cmp_key>, cmp_key>::iterator it = mp.begin(); it != mp.end(); it++) {
        for (map<double, pair<set<int>, set<int> >, cmp_key>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            set<int> up = it2->second.first;
            set<int> down = it2->second.second;
            for (set<int>::iterator it1 = up.begin(); it1 != up.end(); it1++) {
                for (set<int>::iterator it2 = down.begin(); it2 != down.end(); it2++) {
                    G[*it2].push_back(*it1);  // down -> up
                    inDegree[*it1]++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0 && !visited[i]) {
            visited[i] = true;
            q.push(i);
        }
    }

    int cnt = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        cnt++;
        if (cnt == n) {
            printf("%d\n", cur + 1);
        } else {
            printf("%d ", cur + 1);
        }

        for (int i = 0; i < G[cur].size(); i++) {
            int v = G[cur][i];
            if (--inDegree[v] == 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    //freopen("d1.in", "r", stdin);
    //freopen("d.ans", "w", stdout);
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}

/*
3
4
3 4 7 1 7 6
7 6 1 6 3 4
1 6 1 1 3 4
7 1 3 4 1 1
14
0 0 3 0 2 3
2 3 3 0 12 0
2 3 12 0 4 5
4 5 12 0 5 6
5 6 12 0 12 4
5 6 12 4 12 8
5 6 12 8 4 7
4 7 12 8 0 8
4 7 0 8 2 5
4 7 2 5 5 6
5 6 2 5 4 5
4 5 2 5 2 3
2 3 2 5 0 0
0 0 2 5 0 8
4
0 0 3 0 2 2
3 0 3 2 2 2
2 2 0 2 1 1
0 2 0 0 1 1
*/
