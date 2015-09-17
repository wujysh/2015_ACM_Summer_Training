#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20010;

char s[MAXN * 2], sfan[MAXN * 2], sans1[MAXN], sans2[MAXN];
int n, nCase;

int get_mnstring(char *x) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n) {
        k = 0;
        while (x[i + k] == x[j + k] && k < n) k++;
        if (k == n) {
            return min(i, j);
        }
        if (x[i + k] < x[j + k]) {
            if (i + k + 1 > j) {
                i = i + k + 1;
            } else {
                i = j + 1;
            }
        } else if (j + k + 1 > i) {
            j = j + k + 1;
        } else {
            j = i + 1;
        }
    }
    return min(i, j);
}

int get_mxstring(char *x) {
    int i = 0, j = 1, k;
    while (i < n && j < n) {
        k = 0;
        while (x[i + k] == x[j + k] && k < n) k++;
        if (k == n) {
            i = max(i, j);
            j = i + 1;
        } else {
            if (x[i + k] < x[j + k]) {
                if (i + k + 1 > j) {
                    i = i + k + 1;
                } else {
                    i = j + 1;
                }
            } else if (j + k + 1 > i) {
                j = j + k + 1;
            } else {
                j = i + 1;
            }
        }
    }
    if (j >= n) {
        return i;
    }
    return j;
}

void input() {
    scanf("%d", &n);
    scanf("%s", s);
}

void solve() {
    for (int i = 0; i < n; i++) {
        s[i + n] = sfan[n - i - 1] = sfan[2 * n - i - 1] = s[i];
    }
    s[n + n] = sfan[n + n] = '\0';

    int ans1 = get_mnstring(s), ans2 = get_mxstring(sfan);

    for (int i = 0; i < n; i++) {
        sans1[i] = s[ans1 + i];
        sans2[i] = sfan[ans2 + i];
    }
    sans1[n] = sans2[n] = '\0';

    if (strcmp(sans2, sans1) > 0) {
        printf("%d 1\n", n - ans2);
    } else if (strcmp(sans2, sans1) < 0) {
        printf("%d 0\n", ans1 + 1);
    } else if (n - ans2 < ans1 + 1) {
        printf("%d 1\n", n - ans2);
    } else {
        printf("%d 0\n", ans1 + 1);
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
