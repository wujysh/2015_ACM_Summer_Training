#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1000010;

int ans1, ans2, ans3, n, nCase, cCase;
vector<int> v1, v2;
vector<set<int> > s1, s2;

struct Cluster {
    int c1, c2;
    Cluster() {}
    Cluster(int _c1, int _c2) : c1(_c1), c2(_c2) {}
} c[MAXN];

void init() {
    v1.clear();
    v2.clear();
    s1.clear();
    s2.clear();
    ans1 = ans2 = ans3 = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &c[i].c1, &c[i].c2);
        v1.push_back(c[i].c1);
        v2.push_back(c[i].c2);
    }
}

void solve() {
    sort(v1.begin(), v1.end());
    v1.erase(unique(v1.begin(), v1.end()), v1.end());
    s1.resize(v1.size());
    sort(v2.begin(), v2.end());
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    s2.resize(v2.size());

    for (int i = 0; i < n; i++) {
        c[i].c1 = lower_bound(v1.begin(), v1.end(), c[i].c1) - v1.begin();
        c[i].c2 = lower_bound(v2.begin(), v2.end(), c[i].c2) - v2.begin();
        s1[c[i].c1].insert(c[i].c2);
        s2[c[i].c2].insert(c[i].c1);
    }

//    for (int i = 0; i < s1.size(); i++) {
//        cout << i << ": " << endl;
//        for (set<int>::iterator it = s1[i].begin(); it != s1[i].end(); it++) {
//            cout << *it << " ";
//        }
//        cout << endl;
//    }
//    for (int i = 0; i < s2.size(); i++) {
//        cout << i << ": " << endl;
//        for (set<int>::iterator it = s2[i].begin(); it != s2[i].end(); it++) {
//            cout << *it << " ";
//        }
//        cout << endl;
//    }

    for (int i = 0; i < s1.size(); i++) {
        if (!s1[i].empty()) {
            if (s1[i].size() == 1) {
                if (s2[*s1[i].begin()].size() == 1) {
                    ans3++;
                }
            } else {
                int m = *s2[*s1[i].begin()].begin();
                bool flag = true;
                for (set<int>::iterator it = s1[i].begin(); it != s1[i].end(); it++) {
                    if (s2[*it].size() > 1 || (s2[*it].size() == 1 && *s2[*it].begin() != m)) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    ans1++;
                }
            }
        }
    }
    for (int i = 0; i < s2.size(); i++) {
        if (!s2[i].empty()) {
            if (s2[i].size() > 1) {
                int m = *s1[*s2[i].begin()].begin();
                bool flag = true;
                for (set<int>::iterator it = s2[i].begin(); it != s2[i].end(); it++) {
                    if (s1[*it].size() > 1 || (s1[*it].size() == 1 && *s1[*it].begin() != m)) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    ans2++;
                }
            }
        }
    }

    printf("Case #%d: %d %d %d\n", ++cCase, ans1, ans2, ans3);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
