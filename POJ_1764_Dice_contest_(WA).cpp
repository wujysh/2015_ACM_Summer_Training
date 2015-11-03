#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int INF = 0x7fffffff;
const int OFFSET = 50;
const int MARGIN = 50;
const int MAX_BIND = 500;
const int MAXN = OFFSET + MARGIN + MAX_BIND + 1;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {-1, 1, 0, 0};

/*
  1
  2
3 6 4
  4
*/
int dice_score[6], f[MAXN][4][36], fmin[MAXN][4], x1, y1, x2, y2;

vector<int> initial_dice;

void roll(vector<int> &dice, int direction) {
    int tmp;
    switch (direction) {
        case 0:  // up
            tmp = dice[1];  dice[1] = dice[5];  dice[5] = dice[4];  dice[4] = dice[0];  dice[0] = tmp;
            break;
        case 1:  // down
            tmp = dice[0];  dice[0] = dice[4];  dice[4] = dice[5];  dice[5] = dice[1];  dice[1] = tmp;
            break;
        case 2:  // right
            tmp = dice[0];  dice[0] = dice[2];  dice[2] = dice[5];  dice[5] = dice[3];  dice[3] = tmp;
            break;
        case 3:  // left
            tmp = dice[3];  dice[3] = dice[5];  dice[5] = dice[2];  dice[2] = dice[0];  dice[0] = tmp;
            break;
    }
}

void init() {
    for (int i = 0; i < 6; i++) {
        initial_dice.push_back(i);
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < 4; j++) {
            fmin[i][j] = INF;
            for (int k = 0; k < 36; k++) {
                f[i][j][k] = INF;
            }
        }
    }
}

void input() {
    for (int i = 0; i < 6; i++) {
        scanf("%d", &dice_score[i]);
    }
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
}

void solve() {
    y1 = 4 - y1;
    y2 = 4 - y2;
    x2 -= x1;
    if (x2 < 0) {
        x2 -= x2;
        swap(dice_score[2], dice_score[3]);
    }

    // Dijkstra
    set<pair<int, pair<pair<int, int>, vector<int> > > > q;
    q.insert(make_pair(0, make_pair(make_pair(OFFSET+0, y1), initial_dice)));
    while (!q.empty()) {
        int score = q.begin()->first;
        int x = q.begin()->second.first.first;
        int y = q.begin()->second.first.second;
        vector<int> dice = q.begin()->second.second;
        q.erase(q.begin());

        if (f[x][y][dice[0]*6+dice[1]] <= score) continue;

        f[x][y][dice[0]*6+dice[1]] = score;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= MAXN || ny >= 4) continue;
            vector<int> ndice = dice;
            roll(ndice, i);
            q.insert(make_pair(score+dice_score[ndice[0]], make_pair(make_pair(nx, ny), ndice)));
        }
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 36; k++) {
                fmin[i][j] = min(fmin[i][j], f[i][j][k]);
            }
        }
    }

    int loop_len = 7, loop_diff, base = OFFSET + MAX_BIND;
    bool loop_ok;
    do {
        loop_ok = true;
        loop_len++;
        loop_diff = fmin[base][0] - fmin[base-loop_len][0];
        for (int i = 0; i < loop_len; i++) {
            for (int j = 0; j < 4; j++) {
                if (fmin[base-i][j] - loop_diff != fmin[base-i-loop_len][j]) {
                    loop_ok = false;
                }
            }
        }
    } while (!loop_ok);

    if (x2 <= MAX_BIND) {
        printf("%d\n", fmin[OFFSET+x2][y2]);
    } else {
        int loop_count = 1 + (x2 - MAX_BIND) / loop_len;
        int index = OFFSET + x2 - loop_len * loop_count;
        printf("%lld\n", fmin[index][y2] + (long long) loop_diff * loop_count);
    }
}

int main() {
    init();
    input();
    solve();
    return 0;
}
