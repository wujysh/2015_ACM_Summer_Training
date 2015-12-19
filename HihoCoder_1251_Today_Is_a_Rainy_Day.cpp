#include <unordered_map>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 115;
const int INF = 0x3f3f3f3f;

int n, ans;
char s1[MAXN], s2[MAXN];
int cnt[6];
priority_queue<int

struct State {
    int m[6][6], step;

    int sum() const {
        int ret = 0;
        for (int i = 0; i < 6; i++) {
            ret += m[i][i];
        }
        return ret;
    }
    int c() {
        int ret = 0;
        for (int j = 0; j < 6; j++) {
			int Max = 0, index = -1;
			for (int i = 0; i < 6; i++) {
				if (i == j) continue;
				if (m[i][j] > Max) {
					Max = m[i][j];
					index = i;
					ret += m[i][j];
				}
			}
			ret -= m[index][j] - 1;
		}
        return ret;
    }
    bool isTarget() {
        for (int i = 0; i < 6; i++) {
            if (m[i][i] != cnt[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator < (const State &b) const {
		int suma = sum(), sumb = b.sum();
		if (suma == sumb) {
			return step > b.step;
		}
		return suma < sumb;
    }
	bool operator == (const State &b) const {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (m[i][j] != b.m[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
} initial;
priority_queue<State> q;

struct StateHasher {
	size_t operator() (const State &b) const {
		size_t ret;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				ret += hash<int>()(b.m[i][j]) * pow(6, i*6+j);
			}
		}
	}
};
unordered_map<State, bool, StateHasher> visited;

void init() {
    ans = INF;
    while (!q.empty()) {
		q.pop();
	}
	visited.clear();

    n = strlen(s1);

    memset(cnt, 0, sizeof(cnt));
    memset(initial.m, 0, sizeof(initial.m));
    initial.step = 0;
    for (int i = 0; i < n; i++) {
        initial.m[s1[i]-'1'][s2[i]-'1']++;
        cnt[s1[i]-'1']++;
    }
}

void solve() {
    q.push(initial);
    visited[initial] = true;

    while (!q.empty()) {
        State cur = q.top();
        q.pop();

        if (cur.isTarget()) {
            ans = min(ans, cur.step);
            continue;
        }
        if (cur.c() + cur.step >= ans) continue;

        for (int src = 0; src < 6; src++) {
            for (int des = 0; des < 6; des++) {
                if (src == des) continue;

                State nxt;
                nxt.step = cur.step + 1;
                memcpy(nxt.m, cur.m, sizeof(cur.m));

                for (int i = 0; i < 6; i++) {
                    nxt.m[i][des] += nxt.m[i][src];
                    nxt.m[i][src] = 0;
                }
				
				if (!visited.count(nxt)) {
					visited[nxt] = true;
					q.push(nxt);
				}
            }
        }
        
        for (int i = 0; i < 6; i++) {
			for (int src = 0; src < 6; src++) {
				if (cur.m[i][src] == 0) continue;
				
				State nxt;
                memcpy(nxt.m, cur.m, sizeof(cur.m));
                
                nxt.m[i][i] += nxt.m[i][src];
                nxt.step = cur.step + nxt.m[i][src];
                nxt.m[i][src] = 0;
				
				if (!visited.count(nxt)) {
					visited[nxt] = true;
					q.push(nxt);
				}
                q.push(nxt);
			}
		}
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%s%s", s1, s2)) {
        init();
        solve();
    }
    return 0;
}

/*
22345611
12345611
2234562221
1234561221
2234562211
1234561111
22345622112
12345611111
654321654321654321654321
123456123456123456123456
*/
