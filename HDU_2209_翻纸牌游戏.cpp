#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 21;

struct State {
    int card, step;
    State() {}
    State(int _card, int _step) : card(_card), step(_step) {}
};
queue<State> q;

int initial_state, n;
char line[MAXN];
bool visited[1 << MAXN];

void init() {
    n = strlen(line);
    initial_state = 0;
    for (int i = 0, len = strlen(line); i < len; i++) {
        initial_state = initial_state * 2 + (line[i] - '0');
    }
    while (!q.empty()) {
        q.pop();
    }
    memset(visited, false, sizeof(visited));
}

void change(int &card, int i) {
    if (card & (1 << i)) {
        card -= 1 << i;
    } else {
        card += 1 << i;
    }
}

void solve() {
    q.push(State(initial_state, 0));
    visited[initial_state] = true;
    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.card == 0) {
            printf("%d\n", cur.step);
            return;
        }

        for (int i = 0; i < n; i++) {
            State nxt = cur;
            nxt.step++;
            change(nxt.card, i);
            if (i-1 >= 0) {  // left
                change(nxt.card, i-1);
            }
            if (i+1 < n) {  // right
                change(nxt.card, i+1);
            }
            if (!visited[nxt.card]) {
                visited[nxt.card] = true;
                q.push(nxt);
            }
        }
    }
    printf("NO\n");
}

int main() {
    while (~scanf("%s", line)) {
        init();
        solve();
    }
    return 0;
}
