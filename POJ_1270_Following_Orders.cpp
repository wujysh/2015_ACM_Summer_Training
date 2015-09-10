#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 30;
int n, inDegree[MAXN], cCase;
bool graph[MAXN][MAXN], visited[MAXN];
string name[MAXN];
string line;
map<string, int> idx;
vector<int> ans;

void init() {
    idx.clear();
    memset(inDegree, 0, sizeof(inDegree));
    memset(graph, false, sizeof(graph));
    memset(visited, false, sizeof(visited));
    ans.clear();
}

void input() {
    stringstream ss(line);
    string str;
    vector<string> tmp;
    while (ss >> str) {
        tmp.push_back(str);
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < tmp.size(); i++) {
        if (idx.find(tmp[i]) == idx.end()) {
            idx[tmp[i]] = idx.size();
            name[idx.size()] = tmp[i];
        }
    }
    n = idx.size();

    getline(cin, line);
    stringstream ss1(line);
    string x, y;
    while (ss1 >> x >> y) {
        graph[idx[x]][idx[y]] = true;
        inDegree[idx[y]]++;
    }
}

void dfs(int len) {
    if (len == n) {
        for (int i = 0; i < ans.size(); i++) {
            cout << name[ans[i]];
        }
        cout << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            if (visited[i] || inDegree[i] > 0) continue;

            visited[i] = true;
            for (int j = 1; j <= n; j++) {
                if (graph[i][j]) {
                    inDegree[j]--;
                }
            }
            ans.push_back(i);

            dfs(len+1);

            ans.pop_back();
            for (int j = 1; j <= n; j++) {
                if (graph[i][j]) {
                    inDegree[j]++;
                }
            }
            visited[i] = false;
        }
    }
}

void solve() {
    if (cCase++) {
        cout << endl;
    }
    dfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        init();
        input();
        solve();
    }
    return 0;
}
