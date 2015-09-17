#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 35;

const int dx[6] = {0, -1, 0, 1, 0, 0};
const int dy[6] = {-1, 0, 1, 0, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};
const int INF = 0x3f3f3f3f;

struct State {
    int x, y, z, step;
    State() {}
    State(int _x, int _y, int _z, int _step) : x(_x), y(_y), z(_z), step(_step) {}
} start, target;
queue<State> q;

bool visited[MAXN][MAXN][MAXN];
char graph[MAXN][MAXN][MAXN];
int L, R, C;

void init() {
    while (!q.empty()) {
        q.pop();
    }
    memset(visited, false, sizeof(visited));
}

void input() {
    for (int i = 0; i < L; i++) {
        getchar();
        for (int j = 0; j < R; j++) {
            scanf("%s", graph[i][j]);
            for (int k = 0; k < C; k++) {
                if (graph[i][j][k] == 'S') {
                    start = State(j, k, i, 0);
                } else if (graph[i][j][k] == 'E') {
                    target = State(j, k, i, INF);
                }
            }
        }
    }
}

void solve() {
    q.push(start);
    visited[start.x][start.y][start.z] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == target.x && cur.y == target.y && cur.z == target.z) {
            target.step = cur.step;
            break;
        }

        for (int i = 0; i < 6; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i], nz = cur.z + dz[i];
            if (nx < 0 || ny < 0 || nz < 0 || nx >= R || ny >= C || nz >= L || graph[nz][nx][ny] == '#') continue;
            if (!visited[nx][ny][nz]) {
                visited[nx][ny][nz] = true;
                q.push(State(nx, ny, nz, cur.step+1));
            }
        }
    }

    if (target.step == INF) {
        printf("Trapped!\n");
    } else {
        printf("Escaped in %d minute(s).\n", target.step);
    }
}

int main() {
    while (~scanf("%d%d%d", &L, &R, &C) && (L || R || C)) {
        init();
        input();
        solve();
    }
    return 0;
}
