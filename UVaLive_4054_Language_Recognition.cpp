#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 150010;
const int MAXM = 26;
const int MAXL = 35;
const int P = 31;

int trie[MAXN][MAXM], cnt, n;
bool final_state[MAXN];
vector<pair<int, unsigned long long> > hash[MAXN];

void add(char *s) {
    int len = strlen(s);
    int pos = 0;

    for (int i = 0; i < len; i++) {
        if (trie[pos][s[i] - 'a'] == 0) {
            trie[pos][s[i] - 'a'] = cnt++;
        }
        pos = trie[pos][s[i] - 'a'];
    }

    final_state[pos] = true;
}

void init() {
    memset(trie, 0, sizeof(trie));
    memset(final_state, false, sizeof(final_state));
    cnt = 1;
}

void input() {
    char s[MAXL];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        add(s);
    }
}

void build(int pos) {
    hash[pos].clear();
    if (final_state[pos]) {
        hash[pos].push_back(make_pair(0, 0));
    }

    for (int i = 0; i < 26; i++) {
        if (trie[pos][i]) {
            int v = trie[pos][i];

            build(v);

            for (int j = 0; j < hash[v].size(); j++) {
                hash[pos].push_back(make_pair(hash[v][j].first + 1, i + hash[v][j].second * P));
            }
        }
    }
}

void solve() {
    build(0);
    sort(hash, hash+cnt);

    printf("%d\n", unique(hash, hash+cnt) - hash);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
