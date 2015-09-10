#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 500010;

int P, Q, cnt;
string str;

struct Node {
    int flag, w;
    int next[26];
} node[MAXN];

void init() {
    memset(node, 0, sizeof(node));
    cnt = 1;
}

void insert(string str, int flag) {
    int id = 0;
    for (int i = 0; i < str.size(); i++) {
        if (node[id].next[str[i] - 'a'] == 0) {
            node[id].next[str[i] - 'a'] = cnt++;
        }
        id = node[id].next[str[i] - 'a'];
        if (node[id].flag != flag) {  // add only once for the same word
            node[id].w++;
            node[id].flag = flag;
        }
    }
}

int query(string str) {
    int id = 0;
    for (int i = 0; i < str.size(); i++) {
        if (node[id].next[str[i] - 'a'] != 0) {
            id = node[id].next[str[i] - 'a'];
        } else {
            return 0;
        }
    }
    return node[id].w;
}

void input() {
    while (P--) {
        cin >> str;
        for (int j = 0; j < str.size(); j++) {
            insert(str.substr(j), P);
        }
    }
}

void solve() {
    cin >> Q;
    while (Q--) {
        cin >> str;
        cout << query(str) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> P) {
        init();
        input();
        solve();
    }
    return 0;
}
