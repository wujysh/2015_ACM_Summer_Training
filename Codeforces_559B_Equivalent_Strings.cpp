#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 200010;
char str1[MAXN], str2[MAXN];

bool equivalent(int l1, int l2, int len) {
    if (len % 2 == 1) {
        return strncmp(str1 + l1, str2 + l2, len);
    }
    int hlen = len / 2;
    if (equivalent(l1, l2+hlen, hlen) && equivalent(l1+hlen, l2, hlen)) return true;
    if (equivalent(l1, l2, hlen) && equivalent(l1+hlen, l2+hlen, hlen)) return true;
    return false;
}

int main() {
    while (gets(str1)) {
        gets(str2);
        if (equivalent(0, 0, strlen(str1))) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
