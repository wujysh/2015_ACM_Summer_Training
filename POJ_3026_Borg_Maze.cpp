#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 55;
const int MAXA = 110;
const int MAXM = 10010;
const int dx[4] = { -1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int nCase, x, y, ans, cnt, cnt2, id[MAXN][MAXN], father[MAXA], rank_set[MAXA];
char graph[MAXN][MAXN];
bool visited[MAXN][MAXN];

struct State {
    int x, y, step;
    State() {}
    State(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
};

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
} point[MAXA];

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
} edge[MAXM];

void init() {
    ans = cnt = cnt2 = 0;
    memset(id, -1 , sizeof(id));
    for (int i = 0; i < MAXA; i++) {
        father[i] = i;
        rank_set[i] = 1;
    }
}

void input() {
    char line[100];
    gets(line);
    sscanf(line, "%d%d", &x, &y);
    for (int i = 0; i < y; i++) {
        gets(graph[i]);
    }
}

void bfs(int s) {
    queue<State> q;
    memset(visited, false, sizeof(visited));
    q.push(State(point[s].x, point[s].y, 0));
    visited[point[s].x][point[s].y] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (id[cur.x][cur.y] != -1) {
            edge[cnt2++] = Edge(s, id[cur.x][cur.y], cur.step);
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= y || ny >= x) continue;
            if (graph[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(State(nx, ny, cur.step + 1));
            }
        }
    }
}

int find_set(int x) {
    return x == father[x] ? x : x = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void solve() {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (graph[i][j] == 'A' || graph[i][j] == 'S') {
                point[cnt] = Point(i, j);
                id[i][j] = cnt;
                cnt++;
            }
        }
    }

    for (int i = 0; i < cnt; i++) {
        bfs(i);
    }

    sort(edge, edge + cnt2);
    for (int i = 0; i < cnt2; i++) {
        if (find_set(edge[i].u) != find_set(edge[i].v)) {
            union_set(edge[i].u, edge[i].v);
            ans += edge[i].w;
        }
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &nCase);
    getchar();
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
