#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 150010;
const int MAXQ = 110;

struct Person {
    string name;
    int value, pos;
    bool operator < (const Person &b) const {
        if (value == b.value) {
            return pos > b.pos;
        }
        return value < b.value;
    }
} person[MAXN];

priority_queue<Person> q;

struct Node {
    int t, p;
    bool operator < (const Node &b) const {
        return t < b.t;
    }
} node[MAXN];

int ans[MAXN], cnt, nq[MAXQ], k, m, Q, nCase;

void init() {
    while (!q.empty()) {
        q.pop();
    }
    cnt = 0;
}

void input() {
    cin >> k >> m >> Q;
    for (int i = 0; i < k; i++) {
        cin >> person[i].name >> person[i].value;
        person[i].pos = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> node[i].t >> node[i].p;
        node[i].t--;
    }

    for (int i = 0; i < Q; i++) {
        cin >> nq[i];
    }
}

void solve() {
    sort(node, node+m);

    int last = -1;
    for (int i = 0; i < m; i++) {

        for (int j = last+1; j <= node[i].t; j++) {
            q.push(person[j]);
        }

        for (int j = 0; j < node[i].p; j++) {
            if (!q.empty()) {
                Person t = q.top();
                q.pop();
                ans[++cnt] = t.pos;
            }
        }

        last = node[i].t;
    }

    for (int j = last+1; j < k; j++) {
        q.push(person[j]);
    }

    while (!q.empty()) {
        Person t = q.top();
        q.pop();
        ans[++cnt] = t.pos;
    }

    for (int i = 0; i < Q-1; i++) {
        cout << person[ans[nq[i]]].name << " ";
    }
    cout << person[ans[nq[Q-1]]].name << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}

/*
10
2 1 2
W 100
J 101
1 1
1 2

2 1 3
W 100
J 101
1 1
1 2 3
*/
