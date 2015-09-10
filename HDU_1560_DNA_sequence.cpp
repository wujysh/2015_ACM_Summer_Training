#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 10;
const char DNA[] = {'A', 'T', 'C', 'G'};

char dna[MAXN][MAXN];
int nCase, n, len[MAXN], maxlen;

int h_star(int match[]) {  // 至少还需要多少个A、T、C、G，4项之和作为h()函数
    int h = 0;
    map<char, int> mp;
    for (int i = 0; i < n; i++) {
        map<char, int> cnt;
        for (int j = match[i]; j < len[i]; j++) {
            cnt[dna[i][j]]++;
        }
        for (int j = 0; j < 4; j++) {
            mp[DNA[j]] = max(mp[DNA[j]], cnt[DNA[j]]);
        }
    }
    return mp['A'] + mp['T'] + mp['C'] + mp['G'];
}

bool dfs(int d, int match[], int maxd) {  // d：当前深度，match[]：每个DNA的匹配到的位置，maxd：限制的DFS深度
    if (d + h_star(match) > maxd) return false;

    if (d == maxd) return true;

    for (int i = 0; i < 4; i++) {
        int nmatch[MAXN];
        for (int j = 0; j < n; j++) {
            if (match[j] < len[j] && dna[j][match[j]] == DNA[i]) {
                nmatch[j] = match[j] + 1;
            } else {
                nmatch[j] = match[j];
            }
        }
        if (dfs(d + 1, nmatch, maxd)) return true;
    }
    return false;
}

void init() {
    maxlen = 0;
}

void input() {
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", &dna[i]);
        len[i] = strlen(dna[i]);
        maxlen = max(maxlen, len[i]);
    }
}

void solve() {
    int maxd = maxlen, initial[MAXN] = {0};
    while (!dfs(0, initial, maxd)) {
        maxd++;
    }
    printf("%d\n", maxd);
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
