#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

int n;
set<int> ss;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        while (ss.count(a)) {
            ss.erase(a);
            a++;
        }
        ss.insert(a);
    }

    set<int>::iterator it;
    int last = -1, ans = 0;
    for (it = ss.begin(); it != ss.end(); it++) {
        ans += *it - last - 1;
        last = *it;
    }
    printf("%d\n", ans);
    return 0;
}
