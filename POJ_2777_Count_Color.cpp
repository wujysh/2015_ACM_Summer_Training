#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 300010;

struct Node {
    int l, r, mid;
    int color;
    Node() {}
    Node(int _l, int _r) : l(_l), r(_r), mid((l + r) >> 1), color(1) {}
} node[MAXN * 4];

int L, T, O, color;

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].color = 1;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void push_down(int rt) {
    if (node[rt].color) {
        node[rt << 1].color = node[(rt << 1) | 1].color = node[rt].color;
        node[rt].color = 0;
    }
}

void insert(int l, int r, int c, int rt) {
    if (l <= node[rt].l && node[rt].r <= r) {
        node[rt].color = 1 << c;
    } else {
        push_down(rt);
        if (r <= node[rt].mid) {
            insert(l, r, c, rt << 1);
        } else if (l > node[rt].mid) {
            insert(l, r, c, (rt << 1) | 1);
        } else {
            insert(l, node[rt].mid, c, rt << 1);
            insert(node[rt].mid + 1, r, c, (rt << 1) | 1);
        }
    }
}

void query(int l, int r, int rt) {
    if (node[rt].color) {
        color |= node[rt].color;
    } else {
        if (r <= node[rt].mid) {
            query(l, r, rt << 1);
        } else if (l > node[rt].mid) {
            query(l, r, (rt << 1) | 1);
        } else {
            query(l, node[rt].mid, rt << 1);
            query(node[rt].mid + 1, r, (rt << 1) | 1);
        }
    }
}

void init() {
    build(1, L, 1);
}

void solve() {
    char op;
    int A, B, C;
    for (int i = 0; i < O; i++) {
        getchar();
        scanf("%c", &op);
        if (op == 'C') {
            scanf("%d%d%d", &A, &B, &C);
            insert(A, B, C - 1, 1);
        } else if (op == 'P') {
            scanf("%d%d", &A, &B);
            color = 0;
            int cnt = 0;
            query(A, B, 1);
            for (int i = 0; i < T; i++) {
                if (color & (1 << i)) {
                    cnt++;
                }
            }
            printf("%d\n", cnt);
        }
    }
}

int main() {
    while (~scanf("%d%d%d", &L, &T, &O)) {
        init();
        solve();
    }
    return 0;
}
