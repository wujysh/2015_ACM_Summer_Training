#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0, 0, -1};
const char dir[] = {'R', 'D', 'U', 'L'};
const int pos[][2] = {3, 3, 0, 0, 0, 1, 0, 2, 0, 3, 1, 0, 1, 1, 1, 2, 1, 3, 2, 0, 2, 1, 2, 2, 2, 3, 3, 0, 3, 1, 3, 2};
const int target[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

char path[100];
int puzzle[16], nCase, zero;

int h_star() {
    int h = 0;
    for (int i = 0; i < 16; i++) {
        int x = puzzle[i];
        if (x == 0) continue;
        h += abs(i / 4 - pos[x][0]) + abs(i % 4 - pos[x][1]);
    }
    return h;
}

bool solvable() {
    int cnt = 0;
    for (int i = 0; i < 16; i++) {
        if (puzzle[i] == 0) {
            cnt += 3 - i / 4;
        } else {
            for (int j = 0; j < i; j++) {
                if (puzzle[j] && puzzle[j] > puzzle[i]) {
                    cnt++;
                }
            }
        }
    }
    return !(cnt & 1);
}

bool dfs(int zero, int pre, int d, int maxd) {
    if (d + h_star() > maxd) return false;

    if (d == maxd) {
        return memcmp(puzzle, target, sizeof(target)) == 0;
    }

    int x = zero / 4, y = zero % 4;
    for (int i = 0; i < 4; i++) {
        if (pre + i == 3) continue;  // go back
        int nx = x + dx[i], ny = y + dy[i];
        int nzero = 4 * nx + ny;
        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
        swap(puzzle[zero], puzzle[nzero]);
        path[d] = dir[i];
        if (dfs(nzero, i, d + 1, maxd)) return true;
        swap(puzzle[zero], puzzle[nzero]);
    }
    return false;
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        for (int i = 0; i < 16; i++) {
            scanf("%d", &puzzle[i]);
            if (puzzle[i] == 0) {
                zero = i;
            }
        }
        if (solvable()) {
            int maxd = 0;
            while (!dfs(zero, -1, 0, maxd)) {
                maxd++;
            }
            path[maxd] = '\0';
            printf("%s\n", path);
        } else {
            printf("This puzzle is not solvable.\n");
        }
    }
    return 0;
}
