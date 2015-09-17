#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 210;
const int INF = 0x3f3f3f3f;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

struct Status {
    int x, y, step;
    Status() {}
    Status(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
} startY, startM;

char graph[MAXN][MAXN];
int dis[MAXN][MAXN][2], ans, n, m;
bool visited[MAXN][MAXN];
vector<Status> kfc;

void init() {
    memset(dis, 0x3f, sizeof(dis));
    kfc.clear();
    ans = INF;
}

void input() {
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", graph[i]);
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == 'Y') {
                startY = Status(i, j, 0);
            } else if (graph[i][j] == 'M') {
                startM = Status(i, j, 0);
            } else if (graph[i][j] == '@') {
                kfc.push_back(Status(i, j, 0));
            }
        }
    }
}

void bfs(int who) {
    queue<Status> q;
    memset(visited, false, sizeof(visited));

    if (who == 0) {
        q.push(startY);
        visited[startY.x][startY.y] = true;
    } else {
        q.push(startM);
        visited[startM.x][startM.y] = true;
    }

    while (!q.empty()) {
        Status cur = q.front();
        q.pop();

        if (graph[cur.x][cur.y] == '@') {
            dis[cur.x][cur.y][who] = min(dis[cur.x][cur.y][who], cur.step);
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || graph[nx][ny] == '#') continue;
            if (!visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(Status(nx, ny, cur.step+1));
            }
        }
    }
}

void solve() {
    bfs(0);
    bfs(1);

    for (int i = 0; i < kfc.size(); i++) {
        ans = min(ans, dis[kfc[i].x][kfc[i].y][0] + dis[kfc[i].x][kfc[i].y][1]);
    }

    printf("%d\n", ans * 11);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        input();
        solve();
    }
    return 0;
}
