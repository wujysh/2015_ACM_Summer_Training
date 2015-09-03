#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 8;

struct Node {
    int a[6];

} node[MAXN];

int nCase, cCase, x[MAXN], offset[MAXN];

void init() {
    for (int i = 0; i < 7; i++) {
        x[i] = i;
    }
}

void input() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &node[i].a[j]);
        }
    }
}

bool judge() {
    for (int i = 1; i < 6; i++) {
        if (node[x[i]].a[(offset[i] - 1 + 6) % 6] != node[x[i + 1]].a[(offset[i + 1] + 1) % 6]) {
            return false;
        }
    }
    if (node[x[6]].a[(offset[6] - 1 + 6) % 6] != node[x[1]].a[(offset[1] + 1) % 6]) {
        return false;
    }
    return true;
}

void solve() {
    printf("Case %d:", ++cCase);

    do {
        memset(offset, 0, sizeof(offset));

        for (int i = 0; i < 6; i++) {
            if (node[x[0]].a[i] == 1) {
                offset[0] = i;
                break;
            }
        }

        bool flag = true;

        for (int i = 1; i < 7; i++) {
            for (int j = 0; j < 6; j++) {
                if (node[x[i]].a[j] == node[x[0]].a[(i - 1 + offset[0]) % 6]) {
                    offset[i] = j;
                    break;
                }
            }
            if (i > 1) {
                if (node[x[i]].a[(offset[i] + 1) % 6] != node[x[i - 1]].a[(offset[i - 1] - 1 + 6) % 6]) {
                    flag = false;
                    break;
                }
            }
        }

        if (node[x[6]].a[(offset[6] - 1 + 6) % 6] != node[x[1]].a[(offset[1] + 1) % 6]) {
            flag = false;
        }

        if (flag) {
            for (int i = 0; i < 7; i++) {
                printf(" %d", x[i]);
            }
            printf("\n");
            return;
        }
    } while (next_permutation(x, x + 7));

    printf(" No solution\n");
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
