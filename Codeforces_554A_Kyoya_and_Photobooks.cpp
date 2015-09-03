#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <set>
using namespace std;

const int MAXN = 30;

char str[MAXN];

int solve1() {
    int len = strlen(str);
    return 25 * (len+1) + 1;
}

int solve2() {
    string s = string(str);
    set<string> st;
    for (int i = 0; i <= s.size(); i++) {
        string head = s.substr(0, i);
        string tail = s.substr(i);
        for (int j = 0; j < 26; j++) {
            string t = head + char(j + 'a') + tail;
            st.insert(t);
        }
    }
    return st.size();
}

int main() {
    scanf("%s", str);
    //printf("%d\n", solve1());
    printf("%d\n", solve2());
    return 0;
}

