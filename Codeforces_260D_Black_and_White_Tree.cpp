#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

struct Node {
    int id, s;
    Node() {}
    Node(int _id, int _s) : id(_id), s(_s) {}
};
queue<Node> q1, q2;

int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int c, s;
        scanf("%d%d", &c, &s);
        if (c == 1) {
            q1.push(Node(i, s));
        } else {
            q2.push(Node(i, s));
        }
    }

    while (!q1.empty() && !q2.empty()) {
        Node t1 = q1.front(), t2 = q2.front();
        q1.pop();
        q2.pop();

        int t = min(t1.s, t2.s);
        printf("%d %d %d\n", t1.id, t2.id, t);
        t1.s -= t;
        t2.s -= t;
        if (t1.s > 0) {
            q1.push(t1);
        } else if (t2.s > 0) {
            q2.push(t2);
        } else if (!q1.empty()) {
            q2.push(t2);
        } else {
            q1.push(t1);
        }
    }

    return 0;
}
