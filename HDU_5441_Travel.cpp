#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
using namespace std;

const int MAXN = 20010;
const int MAXQ = 5010;
const int MAXM = 100010;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &b) const {
        return w < b.w;
    }
} edge[MAXM];

struct Node {
    int id, x;
    bool operator < (const Node &b) const {
        return x < b.x;
    }
} node[MAXQ];

int nCase, n, m, q, father[MAXN], rank_set[MAXN], cnt_set[MAXN];
long long ans[MAXQ];
set<int> ss;

int find_set(int x) {
    return father[x] == x ? x : father[x] = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
        cnt_set[b] += cnt_set[a];
        ss.insert(b);
        if (ss.find(a) != ss.end()) {
            ss.erase(a);
        }
    } else {
        father[b] = a;
        cnt_set[a] += cnt_set[b];
        ss.insert(a);
        if (ss.find(b) != ss.end()) {
            ss.erase(b);
        }
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void init() {
    for (int i = 0; i < MAXN; i++) {
        father[i] = i;
        rank_set[i] = cnt_set[i] = 1;
    }
    ss.clear();
}

void input() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d", &node[i].x);
        node[i].id = i;
    }
}

void solve() {
    sort(edge, edge+m);
    sort(node, node+q);

    int last = 0;
    for (int i = 0; i < q; i++) {
        for (int j = last; j < m; j++) {
            if (edge[j].w > node[i].x) {
                last = j;
                break;
            }
            //cout << edge[j].u << " " << edge[j].v << endl;
            union_set(edge[j].u, edge[j].v);
        }

        ans[node[i].id] = 0;
        for (set<int>::iterator it = ss.begin(); it != ss.end(); it++) {
            //cout << *it << endl;
            ans[node[i].id] += cnt_set[*it] * (cnt_set[*it] - 1);
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%I64d\n", ans[i]);
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}

/*
1
5 5 3
2 3 6334
1 5 15724
3 5 5705
4 3 12382
1 3 21726
6000
10000
13000
*/
