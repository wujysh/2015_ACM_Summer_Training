#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;

map<string, int> mp;
int n, cnt;
string email[MAXN];
vector<int> v[MAXN];

void init() {
    mp.clear();
    for (int i = 0; i < MAXN; i++) {
        v[i].clear();
    }
    cnt = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> email[i];
    }
}

string getValid(string str) {
    string ret = "";

    int posOfAt = -1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
        if (str[i] == '@') {
            posOfAt = i;
        }
    }

    string t = str.substr(posOfAt+1);
    if (t == "bmail.com") {
        for (int i = 0; i < posOfAt && str[i] != '+'; i++) {
            if (str[i] != '.') {
                ret += str[i];
            }
        }
    } else {
        for (int i = 0; i < posOfAt; i++) {
            ret += str[i];
        }
    }
    ret += '@' + t;

    return ret;
}

void solve() {
    for (int i = 0; i < n; i++) {
        string valid = getValid(email[i]);
        if (mp.find(valid) != mp.end()) {
            v[mp[valid]].push_back(i);
        } else {
            mp[valid] = ++cnt;
            v[cnt].push_back(i);
        }
    }

    cout << mp.size() << endl;

    for (int i = 1; i <= cnt; i++) {
        cout << v[i].size() << " ";
        for (int j = 0; j < v[i].size()-1; j++) {
            cout << email[v[i][j]] << " ";
        }
        cout << email[v[i][v[i].size()-1]] << endl;
    }
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
