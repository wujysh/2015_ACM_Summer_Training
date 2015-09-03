#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

int n, m, cnt[MAXN];

int main() {
    while (~scanf("%d%d", &n, &m)) {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= m; i++) {
            int Max = 0, index = 1;
            for (int j = 1; j <= n; j++) {
                int a;
                scanf("%d", &a);
                if (a > Max) {
                    Max = a;
                    index = j;
                }
            }
            cnt[index]++;
        }

        int Max = 0, index = 1;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] > Max) {
                Max = cnt[i];
                index = i;
            }
        }

        printf("%d\n", index);
    }
    return 0;
}
