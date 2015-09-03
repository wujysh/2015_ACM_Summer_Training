#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct Node {
    int a[6];
    bool operator < (const Node &b) const {
        for (int i = 0; i < 6; i++) {
            if (a[i] < b.a[i]) {
                return true;
            }
        }
        return false;
    }
} t;
vector<Node> m;

int cCase;
char op[5];

void dfs(int x, int rest) {
    if (x == 7) {
        if (rest == 0) {
            m.push_back(t);
        }
        return;
    }
    for (int i = 0; i <= rest; i++) {
        t.a[x-1] = i;
        dfs(x+1, rest - i);
    }
}

//15504
int main() {
    dfs(1, 15);

    while (~scanf("%s", op) && op[0] != 'e') {
        printf("Case %d:", ++cCase);

        if (op[0] == 'm') {
            Node x;
            for (int i = 0; i < 6; i++) {
                scanf("%d", &x.a[i]);
            }
            for (int i = 0; i < m.size(); i++) {
                bool flag = true;
                for (int j = 0; j < 6; j++) {
                    if (m[i].a[j] != x.a[j]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    printf(" %d\n", i);
                    break;
                }
            }

        } else if (op[0] == 'u') {
            int n;
            scanf("%d", &n);
            for (int i = 0; i < 6; i++) {
                printf(" %d", m[n].a[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
