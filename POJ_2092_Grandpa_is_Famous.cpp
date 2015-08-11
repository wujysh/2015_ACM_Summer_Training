#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 10010;

struct Node {
    int x, cnt;
    Node() {}
    Node(int _x, int _cnt) : x(_x), cnt(_cnt) {}
    bool operator < (const Node &b) const {
        if (cnt == b.cnt) {
            return x < b.x;
        }
        return cnt > b.cnt;
    }
} players[MAXN];

int n, m;

void init() {
    memset(players, 0, sizeof(players));
}

void input() {
    for (int i = 0; i < n*m; i++) {
        int a;
        scanf("%d", &a);
        players[a].x = a;
        players[a].cnt++;
    }
}

void solve() {
    sort(players, players+MAXN);

    int cnt = 0;
    for (int i = 0; i < MAXN; i++) {
        if (players[i].cnt == players[1].cnt) {
            if (cnt++) printf(" ");
            printf("%d", players[i].x);
        } else if (players[i].cnt < players[1].cnt) {
            break;
        }
    }
    printf("\n");
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        init();
        input();
        solve();
    }
    return 0;
}
