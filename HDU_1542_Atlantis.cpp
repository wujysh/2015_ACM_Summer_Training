#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;

struct Node {
    int l, r, mid, cover;
    double len;
    Node() {}
    Node(int _l, int _r, int _mid, int _cover, double _len) {}
} node[MAXN * 15];

struct Square {
    double x1, x2, y1, y2;
    Square() {}
    Square(double _x1, double _y1, double _x2, double _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
} square[MAXN];

struct Edge {
    double x;
    int idy1, idy2;
    int cover;  // 1 or -1
    Edge(double _x, int _idy1, int _idy2, int _cover) : x(_x), idy1(_idy1), idy2(_idy2), cover(_cover) {}
    bool operator < (const Edge &t) const {
        return x < t.x;
    }
};
vector<Edge> edge;

vector<double> yy;
double ans;
int cCase, n;

void build(int l, int r, int rt) {
    //cout << "build: " << l << " " << r << " " << rt << endl;
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].cover = 0;
    node[rt].len = 0;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void push_down(int rt) {
    if (node[rt].cover) {
        node[rt << 1].cover += node[rt].cover;
        node[(rt << 1) | 1].cover += node[rt].cover;
        node[rt].cover = 0;
    }
}

void push_up(int rt) {
    if (node[rt].cover) {
        node[rt].len = yy[node[rt].r+1] - yy[node[rt].l];
    } else {
        node[rt].len = node[rt << 1].len + node[(rt << 1) | 1].len;
    }
}

void insert(int l, int r, int c, int rt) {
    //cout << "insert: " << l << " " << r << " " << rt << endl;
    if (l <= node[rt].l && node[rt].r <= r) {
        node[rt].cover += c;
        push_up(rt);
    } else {
        //push_down(rt);
        if (r <= node[rt].mid) {
            insert(l, r, c, rt << 1);
        } else if (l > node[rt].mid) {
            insert(l, r, c, (rt << 1) | 1);
        } else {
            insert(l, node[rt].mid, c, rt << 1);
            insert(node[rt].mid + 1, r, c, (rt << 1) | 1);
        }
        push_up(rt);
    }
}

double query(int l, int r, int rt) {
    //cout << "query: " << l << " " << r << " " << rt << endl;
    if (l <= node[rt].l && node[rt].r <= r) {
        return node[rt].len;
    } else {
        push_down(rt);
        if (r <= node[rt].mid) {
            return query(l, r, rt << 1);
        } else if (l > node[rt].mid) {
            return query(l, r, (rt << 1) | 1);
        } else {
            return query(l, node[rt].mid, rt << 1) + query(node[rt].mid + 1, r, (rt << 1) | 1);
        }
    }
}

void init() {
    yy.clear();
    edge.clear();
    ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf%lf", &square[i].x1, &square[i].y1, &square[i].x2, &square[i].y2);
        yy.push_back(square[i].y1);
        yy.push_back(square[i].y2);
    }
}

void solve() {
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for (int i = 0; i < n; i++) {
        int y1 = lower_bound(yy.begin(), yy.end(), square[i].y1) - yy.begin();
        int y2 = lower_bound(yy.begin(), yy.end(), square[i].y2) - yy.begin();
        edge.push_back(Edge(square[i].x1, y1, y2, 1));
        edge.push_back(Edge(square[i].x2, y1, y2, -1));
    }
    sort(edge.begin(), edge.end());

    build(0, yy.size() - 1, 1);

    for (int i = 0; i < 2 * n - 1; i++) {
        //cout << "edge: " << edge[i].idy1 << " " << edge[i].idy2 << " " << edge[i].cover << endl;
        insert(edge[i].idy1, edge[i].idy2 - 1, edge[i].cover, 1);
        ans += query(0, yy.size() - 1, 1) * (edge[i + 1].x - edge[i].x);
    }

    printf("Test case #%d\n", ++cCase);
    printf("Total explored area: %.2f\n\n", ans);
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        input();
        solve();
    }
    return 0;
}
