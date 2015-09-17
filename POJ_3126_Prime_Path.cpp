#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 10010;

struct Node {
    int a, b, c, d, step;
    Node() {}
    Node(int _a, int _b, int _c, int _d, int _step) : a(_a), b(_b), c(_c), d(_d), step(_step) {}
    int num() {
        return a + b * 10 + c * 100 + d * 1000;
    }
};

bool visited[MAXN];
int l, r, nCase;

bool isPrime(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

void solve() {
    queue<Node> q;
    memset(visited, false, sizeof(visited));

    Node start = Node(l % 10, (l/10) % 10, (l/100) % 10, l/1000, 0);
    Node target = Node(r % 10, (r/10) % 10, (r/100) % 10, r/1000, 0);

    q.push(start);
    visited[start.num()] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.a == target.a && cur.b == target.b && cur.c == target.c && cur.d == target.d) {
            printf("%d\n", cur.step);
            return;
        }

        for (int i = 1; i <= 9; i += 2) {
            if (i != cur.a) {
                Node nxt = Node(i, cur.b, cur.c, cur.d, cur.step+1);
                int num = nxt.num();
                if (!visited[num] && isPrime(num)) {
                    visited[num] = true;
                    q.push(nxt);
                }
            }
        }

        for (int i = 0; i <= 9; i++) {
            if (i != cur.b) {
                Node nxt = Node(cur.a, i, cur.c, cur.d, cur.step+1);
                int num = nxt.num();
                if (!visited[num] && isPrime(num)) {
                    visited[num] = true;
                    q.push(nxt);
                }
            }
        }

        for (int i = 0; i <= 9; i++) {
            if (i != cur.c) {
                Node nxt = Node(cur.a, cur.b, i, cur.d, cur.step+1);
                int num = nxt.num();
                if (!visited[num] && isPrime(num)) {
                    visited[num] = true;
                    q.push(nxt);
                }
            }
        }

        for (int i = 1; i <= 9; i++) {
            if (i != cur.d) {
                Node nxt = Node(cur.a, cur.b, cur.c, i, cur.step+1);
                int num = nxt.num();
                if (!visited[num] && isPrime(num)) {
                    visited[num] = true;
                    q.push(nxt);
                }
            }
        }
    }

    printf("Impossible\n");
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d", &l, &r);
        solve();
    }
    return 0;
}
