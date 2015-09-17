#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 5;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

struct Node {
    int x, y, step;
    short l[30];
    Node() {}
    Node(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
};

bool visited[MAXN][MAXN];
int a[MAXN][MAXN];

Node solve() {
    queue<Node> q;
    memset(visited, false, sizeof(visited));

    q.push(Node(0, 0, 0));
    visited[0][0] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.x == 4 && cur.y == 4) {
            return cur;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5 || a[nx][ny] == 1) continue;
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                Node nxt = Node(nx, ny, cur.step+1);
                nxt.l[cur.step] = i;
                q.push(nxt);
            }
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(visited, 0, sizeof(visited));
    Node ans = solve();
    int x, y;
    x = 0, y = 0;
    for (int i = 0; i <= ans.step; i++) {
        printf("(%d, %d)\n", x, y);
        x += dx[ans.l[i]];
        y += dy[ans.l[i]];
    }
    return 0;
}
