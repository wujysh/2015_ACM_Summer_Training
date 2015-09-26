#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100010;

struct Node {
    int index, value;
    Node() {}
    Node(int _index, int _value) : index(_index), value(_value) {}
    bool operator < (const Node &b) const {
        return value > b.value;
    }
};
vector<Node> v;

int father[MAXN], rank_set[MAXN], min_set[MAXN], l_set[MAXN], r_set[MAXN], ansl, ansr, n, a[MAXN], cCase;
long long sum_set[MAXN], ans;

int find_set(int x) {
    return x == father[x] ? x : father[x] = find_set(father[x]);
}

pair<long long, pair<int, int> > union_set(int x, int y) {
    int u = find_set(x), v = find_set(y);
    if (u == v) return make_pair(0, make_pair(0, 0));
    if (rank_set[u] < rank_set[v]) {
        father[u] = v;
        sum_set[v] += sum_set[u];
        min_set[v] = min(min_set[v], min_set[u]);
        l_set[v] = min(l_set[v], l_set[u]);
        r_set[v] = max(r_set[v], r_set[u]);
        return make_pair(sum_set[v], make_pair(l_set[v], r_set[v]));
    } else {
        father[v] = u;
        sum_set[u] += sum_set[v];
        min_set[u] = min(min_set[u], min_set[v]);
        l_set[u] = min(l_set[u], l_set[v]);
        r_set[u] = max(r_set[u], r_set[v]);
        if (rank_set[u] == rank_set[v]) {
            rank_set[u]++;
        }
        return make_pair(sum_set[u], make_pair(l_set[u], r_set[u]));
    }
}

void init() {
    v.clear();
    ans = -1;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        v.push_back(Node(i, a[i]));
        father[i] = i;
        rank_set[i] = 1;
        sum_set[i] = min_set[i] = a[i];
        l_set[i] = r_set[i] = i;
    }
}

void solve() {
    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        int id = v[i].index;
        if (id > 1 && a[id] <= a[id - 1]) {
            pair<long long, pair<int, int> > result = union_set(id, id - 1);
            if (a[id] * result.first > ans) {
                ans = a[id] * result.first;
                ansl = result.second.first;
                ansr = result.second.second;
            }
        }
        if (id < n && a[id] <= a[id + 1]) {
            pair<long long, pair<int, int> > result = union_set(id, id + 1);
            if (a[id] * result.first > ans) {
                ans = a[id] * result.first;
                ansl = result.second.first;
                ansr = result.second.second;
            }
        }
        if ((long long) a[id] * a[id] > ans) {
            ans = (long long) a[id] * a[id];
            ansl = ansr = id;
            if (ans == 0) {
                ansl = ansr = id;
            }
        }
    }

    if (cCase++) {
        printf("\n");
    }
    printf("%lld\n", ans);
    printf("%d %d\n", ansl, ansr);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
