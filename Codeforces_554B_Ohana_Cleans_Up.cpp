#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

int n;
char a[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 1;
        for (int j = i+1; j < n; j++) {
            if (strcmp(a[i], a[j]) == 0) {
                cnt++;
            }
        }
        ans = max(ans, cnt);
    }

    printf("%d\n", ans);

    return 0;
}
