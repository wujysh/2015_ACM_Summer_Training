#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 110;

stack<int> st;
vector<int> G[MAXN], G2[MAXN];
bool inStack[MAXN];
int dfn[MAXN], low[MAXN], belong[MAXN], inDegree[MAXN], outDegree[MAXN], dfn_cnt, cnt, n, inZero, outZero;

void init() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        G2[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(belong, 0, sizeof(belong));
    memset(inStack, false, sizeof(inStack));
    memset(inDegree, 0, sizeof(inDegree));
    memset(outDegree, 0, sizeof(outDegree));
    while (!st.empty()) {
        st.pop();
    }
    dfn_cnt = 1;
    cnt = inZero = outZero = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        int x;
        while (~scanf("%d", &x) && x) {
            G[i].push_back(x);
        }
    }
}

void tarjan(int u) {
    dfn[u] = low[u] = dfn_cnt++;
    st.push(u);
    inStack[u] = true;

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        cnt++;
        while (true) {
            int t = st.top();
            st.pop();
            inStack[t] = false;
            belong[t] = cnt;
            if (t == u) break;
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int u = belong[i], v = belong[G[i][j]];
            if (u != v) {
                G2[u].push_back(v);
                inDegree[v]++;
                outDegree[u]++;
            }
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (inDegree[i] == 0) {
            inZero++;
        }
        if (outDegree[i] == 0) {
            outZero++;
        }
    }

    printf("%d\n", inZero);
    printf("%d\n", cnt == 1 ? 0 : max(inZero, outZero));
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
