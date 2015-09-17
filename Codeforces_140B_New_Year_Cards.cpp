#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 310;
const int INF = 0x3f3f3f3f;

int n, x, p[MAXN][MAXN], ans[MAXN];

struct Node {
    int id, order;
    Node() {}
    Node(int _id, int _order) : id(_id), order(_order) {}
    bool operator < (const Node &b) const {
        return order < b.order;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        p[i][0] = INF;
        for (int j = 1; j <= n; j++) {
            scanf("%d", &x);
            p[i][x] = j;
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        p[0][x] = i;
    }

    vector<Node> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(Node(i, p[0][i]));
        sort(v.begin(), v.end());

        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < v.size(); k++) {
                if (v[k].id != j) {
                    if (p[j][v[k].id] < p[j][ans[j]]) {
                        ans[j] = v[k].id;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        printf("%d ", ans[i]);
    }
    printf("%d\n", ans[n]);

    return 0;
}
