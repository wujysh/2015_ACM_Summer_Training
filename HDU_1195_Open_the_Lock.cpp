#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 4;
const int MAXM = 10000;
int nCase;
bool visited[MAXM];

struct State {
    int digit[MAXN], step;
    State() {}
    State(int num, int _step = 0) : step(_step) {
        for (int i = 3; i >= 0; i--) {
            digit[i] = num % 10;
            num /= 10;
        }
    }
    int toNum() {
        int ans = 0;
        for (int i = 0; i < 4; i++) {
            ans = ans * 10 + digit[i];
        }
        return ans;
    }
} initial_state, target_state;
queue<State> q;

void init() {
    while (!q.empty()) {
        q.pop();
    }
    memset(visited, false, sizeof(visited));
}

void input() {
    int a, b;
    scanf("%d%d", &a, &b);
    initial_state = State(a);
    target_state = State(b);
}

void incDigit(int &x) {
    x++;
    if (x == 10) {
        x = 1;
    }
}

void decDigit(int &x) {
    x--;
    if (x == 0) {
        x = 9;
    }
}

void solve() {
    q.push(initial_state);
    visited[initial_state.toNum()] = true;
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        if (cur.toNum() == target_state.toNum()) {
            printf("%d\n", cur.step);
            return;
        }

        State nxt = cur;  nxt.step++;
        for (int i = 0; i < 4; i++) {
            incDigit(nxt.digit[i]);
            int nNum = nxt.toNum();
            if (!visited[nNum]) {
                visited[nNum] = true;
                q.push(nxt);
            }
            decDigit(nxt.digit[i]);

            decDigit(nxt.digit[i]);
            nNum = nxt.toNum();
            if (!visited[nNum]) {
                visited[nNum] = true;
                q.push(nxt);
            }
            incDigit(nxt.digit[i]);
        }
        for (int i = 1; i < 4; i++) {
            swap(nxt.digit[i-1], nxt.digit[i]);
            int nNum = nxt.toNum();
            if (!visited[nNum]) {
                visited[nNum] = true;
                q.push(nxt);
            }
            swap(nxt.digit[i-1], nxt.digit[i]);
        }
    }
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
