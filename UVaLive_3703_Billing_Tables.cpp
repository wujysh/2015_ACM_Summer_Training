#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

char A[MAXN][20], B[MAXN][20], C[MAXN][MAXN], s[MAXN];
bool valid[MAXN];
int n, num[MAXN], ans, cCase;

struct Trie {
    int next[26010][10], end[26010];
    int cnt, root;

    int newNode() {
        for (int i = 0; i < 10; i++) {
            next[cnt][i] = -1;
        }
        end[cnt] = -1;
        return cnt++;
    }

    void init() {
        cnt = 0;
        root = newNode();
    }

    void insert(char *s1, char *s2, int num) {
        int len = strlen(s1);
        int l = 0, r = 0;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < 10; j++) {
                if (next[l][j] == -1) {
                    next[l][j] = newNode();
                }
                if (end[l] > 0) {
                    end[next[l][j]] = end[l];
                }
                if (next[r][j] == -1) {
                    next[r][j] = newNode();
                }
                if (end[r] > 0) {
                    end[next[r][j]] = end[r];
                }
            }
            end[l] = end[r] = -1;
            if (l == r) {
                for (int j = s1[i]-'0'+1; j < s2[i]-'0'; j++) {
                    end[next[l][j]] = num;
                }
            } else {
                for (int j = s1[i]-'0'+1; j < 10; j++) {
                    end[next[l][j]] = num;
                }
                for (int j = 0; j < s2[i]-'0'; j++) {
                    end[next[r][j]] = num;
                }
            }
            l = next[l][s1[i]-'0'];
            r = next[r][s2[i]-'0'];
        }
        end[l] = num;
        end[r] = num;
    }

    void dfs(int cur) {
        if (end[cur] > 0) {
            ans += valid[end[cur]];
            return;
        }
        if (next[cur][0] == -1) return;

        bool flag = true;
        for (int i = 0; i < 10; i++) {
            dfs(next[cur][i]);
            if (end[next[cur][i]] != end[next[cur][0]]) {
                flag = false;
            }
        }
        if (flag && valid[end[next[cur][0]]] && cur != root) {
            ans -= 9;
            end[cur] = end[next[cur][0]];
        }
    }

    void output(int cur, int len) {
        if (end[cur] > 0) {
            if (valid[end[cur]]) {
                for (int i = 0; i < len; i++) {
                    printf("%c", s[i]);
                }
                printf(" %s\n", C[end[cur]]);
            }
            return;
        }
        if (next[cur][0] == -1) return;
        for (int i = 0; i < 10; i++) {
            s[len] = i + '0';
            output(next[cur][i], len+1);
        }
    }
} trie;

void init() {
    trie.init();
    memset(valid, false, sizeof(valid));
    ans = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%s - %s %s", A[i], B[i], C[i]);
        int len1 = strlen(A[i]), len2 = strlen(B[i]);
        for (int j = len2-1; j >= 0; j--) {
            B[i][j + (len1 - len2)] = B[i][j];
        }
        for (int j = 0; j < len1 - len2; j++) {
            B[i][j] = A[i][j];
        }
        if (strcmp(C[i], "invalid") != 0) {
            valid[i] = true;
        }
        num[i] = i;
        for (int j = 1; j < i; j++) {
            if (strcmp(C[i], C[j]) == 0) {
                num[i] = j;
                break;
            }
        }
    }
}

void solve() {
    for (int i = n; i >= 1; i--) {
        trie.insert(A[i], B[i], num[i]);
    }

    trie.dfs(trie.root);

    if (cCase++) {
        printf("\n");
    }
    printf("%d\n", ans);
    trie.output(trie.root, 0);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
