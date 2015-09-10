#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100010;

int n, x[MAXN], y[MAXN];
vector<int> X, Y;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        X.push_back(x[i]);
        Y.push_back(y[i]);
    }

    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    for (int i = 1; i <= n; i++) {
        int xx = lower_bound(XX.begin(), XX.end(), x[i]);
        int yy = lower_bound(YY.begin(), YY.end(), y[i]);
        v[]
    }


    return 0;
}
