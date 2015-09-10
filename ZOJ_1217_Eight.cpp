#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0, 0, -1};
const char dir[] = {'r', 'd', 'u', 'l'};
const int pos[][2] = {2, 2, 0, 0, 0, 1, 0, 2, 1, 0, 1, 1, 1, 2, 2, 0, 2, 1};
const int target[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

char path[100];
int puzzle[9], nCase, zero;

int h_star() {
    int h = 0;
    for (int i = 0; i < 9; i++) {
        int x = puzzle[i];
        if (x == 0) continue;
        h += abs(i / 3 - pos[x][0]) + abs(i % 3 - pos[x][1]);
    }
    return h;
}

bool solvable() {
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (puzzle[i] == 0) continue;
        for (int j = i+1; j < 9; j++) {
            if (puzzle[j] == 0) continue;
            if (puzzle[i] > puzzle[j]) {
                cnt++;
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

    int x = zero / 3, y = zero % 3;
    for (int i = 0; i < 4; i++) {
        if (pre + i == 3) continue;  // go back
        int nx = x + dx[i], ny = y + dy[i];
        int nzero = 3 * nx + ny;
        if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;
        swap(puzzle[zero], puzzle[nzero]);
        path[d] = dir[i];
        if (dfs(nzero, i, d + 1, maxd)) return true;
        swap(puzzle[zero], puzzle[nzero]);
    }
    return false;
}

int main() {
    char str[5];
    while (~scanf("%s", str)) {
        if (strcmp(str, "x") == 0) {
            zero = 0;
            puzzle[0] = 0;
        } else {
            puzzle[0] = atoi(str);
        }
        for (int i = 1; i < 9; i++) {
            scanf("%s", str);
            if (strcmp(str, "x") == 0) {
                zero = i;
                puzzle[i] = 0;
            } else {
                puzzle[i] = atoi(str);
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
            printf("unsolvable\n");
        }
    }
    return 0;
}
