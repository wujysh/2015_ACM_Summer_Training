#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 510;

int n;
int prefer[MAXN][MAXN], order[MAXN][MAXN], next_choice[MAXN];
int future_husband[MAXN], future_wife[MAXN];
map<string, int> id_man, id_woman;
map<int, string> name_man, name_woman;
queue<int> q;

void init() {
    id_man.clear();
    id_woman.clear();
    name_man.clear();
    name_woman.clear();
    for (int i = 1; i <= n; i++) {
        next_choice[i] = 1;
        future_wife[i] = 0;
        future_husband[i] = 0;
    }
    while (!q.empty()) {
        q.pop();
    }
}

void input() {
    string man, woman;
    for (int i = 1; i <= n; i++) {
        cin >> man;
        if (id_man.find(man) == id_man.end()) {
            id_man[man] = id_man.size();
            name_man[id_man.size()] = man;
        }
        for (int j = 1; j <= n; j++) {
            cin >> woman;
            if (id_woman.find(woman) == id_woman.end()) {
                id_woman[woman] = id_woman.size();
                name_woman[id_woman.size()] = woman;
            }
            prefer[id_man[man]][j] = id_woman[woman];
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> woman;
        for (int j = 1; j <= n; j++) {
            cin >> man;
            order[id_woman[woman]][id_man[man]] = j;
        }
    }
}

void engage(int man, int woman) {
    int m = future_husband[woman];
    if (m) {
        future_wife[m] = 0;
        q.push(m);
    }
    future_wife[man] = woman;
    future_husband[woman] = man;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    while (!q.empty()) {
        int man = q.front();
        q.pop();
        int woman = prefer[man][next_choice[man]++];
        if (!future_husband[woman]) {
            engage(man, woman);
        } else if (order[woman][man] < order[woman][future_husband[woman]]) {
            engage(man, woman);
        } else {
            q.push(man);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << name_man[future_husband[i]] << " " << name_woman[i] << endl;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        init();
        input();
        solve();
    }
    return 0;
}
