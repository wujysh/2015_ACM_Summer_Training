#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXM = 100010;

int n, k, maxD;
vector<int> dis[MAXM];
vector<pair<int, int> > ans;

void init() {
    for (int i = 0; i < MAXM; i++) {
        dis[i].clear();
    }
    ans.clear();
}

void input() {
    for (int i = 1; i <= n; i++) {
        int d;
        scanf("%d", &d);
        dis[d].push_back(i);
        maxD = max(maxD, d);
    }
}

void solve() {
    if (dis[0].size() != 1) {
        printf("-1\n");
        return;
    } else {
        for (int i = 1; i <= maxD; i++) {
            int edge = (i != 1), cnt = 0;
            for (int j = 0; j < dis[i].size(); j++) {
                if (edge == k) {
                    edge = (i != 1);
                    cnt++;
                }
                if (cnt == dis[i-1].size()) {
                    printf("-1\n");
                    return;
                }
                ans.push_back(make_pair(dis[i-1][cnt], dis[i][j]));
                edge++;
            }
        }

        printf("%d\n", n-1);
        for (int i = 0; i < ans.size(); i++) {
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &k)) {
        init();
        input();
        solve();
    }
    return 0;
}
