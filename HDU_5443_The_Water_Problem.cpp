#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
int N, Q, nCase, num[MAXN];

struct Node {
    int l, r, mid;
    int m;
} node[MAXN << 2];

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    if (l == r) {
        node[rt].m = num[l];
    }
    if (l != r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid+1, r, (rt << 1) | 1);
        node[rt].m = max(node[rt << 1].m, node[(rt << 1) | 1].m);
    }
}

int query(int l, int r, int rt) {
    if (l <= node[rt].l && node[rt].r <= r) {
        return node[rt].m;
    } else {
        if (r <= node[rt].mid) {
            return query(l, r, rt << 1);
        } else if (l > node[rt].mid) {
            return query(l, r, (rt << 1) | 1);
        } else {
            return max(query(l, node[rt].mid, rt << 1), query(node[rt].mid+1, r, (rt << 1) | 1));
        }
    }
}

void init() {
}

void input() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &num[i]);
    }
}

void solve() {
    build(1, N, 1);

    scanf("%d", &Q);
    while (Q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r, 1));
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
