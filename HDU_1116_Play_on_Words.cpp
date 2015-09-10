#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 30;
int nCase, n, inDegree[MAXN], outDegree[MAXN], father[MAXN], numOfSet;
map<char, int> idx;

void init() {
    idx.clear();
    memset(inDegree, 0, sizeof(inDegree));
    memset(outDegree, 0, sizeof(outDegree));
    for (int i = 0; i < MAXN; i++) {
        father[i] = i;
    }
    numOfSet = 26;
}

int find_set(int x) {
    return father[x] == x ? x : x = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    father[a] = b;
    numOfSet--;
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        int len = word.size();
        if (idx.find(word[0]) == idx.end()) {
            idx[word[0]] = idx.size();
        }
        inDegree[idx[word[0]]]++;
        if (idx.find(word[len-1]) == idx.end()) {
            idx[word[len-1]] = idx.size();
        }
        outDegree[idx[word[len-1]]]++;
        union_set(idx[word[0]], idx[word[len-1]]);
    }
}

void solve() {
    if (numOfSet == 26 - idx.size() + 1) {  // all connected
        int cntError = 0, cntIn = 0, cntOut = 0;
        for (int i = 1; i <= idx.size(); i++) {
            if (inDegree[i] != outDegree[i]) {
                if (inDegree[i] - outDegree[i] == 1) {
                    cntIn++;
                } else if (outDegree[i] - inDegree[i] == 1) {
                    cntOut++;
                } else {
                    cntError++;
                }
            }
        }
        if (cntError == 0) {
            if (cntIn < 2 && cntOut < 2) {
                cout << "Ordering is possible." << endl;
            } else {
                cout << "The door cannot be opened." << endl;
            }
        } else {
            cout << "The door cannot be opened." << endl;
        }
    } else {
        cout << "The door cannot be opened." << endl;
    }
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
