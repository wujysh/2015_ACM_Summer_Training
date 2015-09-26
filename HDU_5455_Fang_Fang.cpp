#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1000010;

char line[MAXN];
int nCase, cCase;

int solve() {
    int len = strlen(line), firstC = -1, ans = 0;
    if (len == 0) {
        return -1;
    }
    for (int i = 0; i < len; i++) {
        if (line[i] != 'c' && line[i] != 'f') {
            return -1;
        }
    }

    for (int i = 0; i < len; i++) {
        if (line[i] == 'c') {
            firstC = i;
            break;
        }
    }

    if (firstC == -1) {  // only f
        return (len+1) / 2;
    } else {  // c and f
        int cntF = 0;
        for (int i = firstC+1; i < len; i++) {
            if (line[i] == 'f') {
                cntF++;
            } else if (line[i] == 'c') {
                if (cntF < 2) {
                    return -1;
                }
                ans++;
                cntF = 0;
            }
        }

        if (cntF+firstC >= 2) {
            ans++;
        } else {
            return -1;
        }
    }

    return ans;
}

int main() {
    scanf("%d", &nCase);
    getchar();
    while (nCase--) {
        gets(line);
        printf("Case #%d: %d\n", ++cCase, solve());
    }
    return 0;
}
