#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 110;

char str[MAXN];
int n;

int main() {
    while (~scanf("%d", &n)) {
        scanf("%s", str);

        int posF = 0;
        for (int i = 0; i < n; i++) {
            if (str[i] == 'F') {
                posF = i;
                break;
            }
        }

        int cnt = 0, ans = 0, lastA = posF;
        for (int i = posF+1; i < n; i++) {
            if (str[i] == 'A') {
                ans += i - lastA;
                lastA = i;
                cnt++;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}
