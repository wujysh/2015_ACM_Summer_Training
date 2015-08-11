#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1 << 30;
const int maxNode = 1010;
const int maxEdge = 100010;

int n, m, a, b, s, t, k;
int nodeCount, edgeCount, firstEdge[maxNode], to[maxEdge], length[maxEdge], nextEdge[maxEdge], dist[maxNode];
bool visit[maxNode];
priority_queue<pair<int, int> > heap;

void clearEdge() {
    nodeCount = edgeCount = 0;
    memset(firstEdge, -1, sizeof(firstEdge));
}

void addEdge(int u, int v, int w) {
    nodeCount = max(nodeCount, max(u, v));
    to[edgeCount] = v;
    length[edgeCount] = w;
    nextEdge[edgeCount] = firstEdge[u];
    firstEdge[u] = edgeCount++;
}

int solve(vector<pair<pair<int, int>, int> > &edges, int s, int t, int k) {
    clearEdge();
    for (vector<pair<pair<int, int>, int> >::iterator it = edges.begin(); it != edges.end(); it++) {
        addEdge(it->first.second, it->first.first, it->second);
    }
    for (int i = 1; i <= nodeCount; i++) {
        dist[i] = INF;
        visit[i] = false;
    }
    dist[t] = 0;
    while (true) {
        int pivot = 1;
        while (pivot <= nodeCount && visit[pivot]) {
            pivot++;
        }
        if (pivot > nodeCount) {
            break;
        }
        for (int i = 1; i <= nodeCount; i++) {
            if (!visit[i] && dist[i] < dist[pivot]) {
                pivot = i;
            }
        }
        visit[pivot] = true;
        for (int i = firstEdge[pivot]; i != -1; i = nextEdge[i]) {
            if (dist[pivot] + length[i] < dist[to[i]]) {
                dist[to[i]] = dist[pivot] + length[i];
            }
        }
    }
    clearEdge();
    for (vector<pair<pair<int, int>, int> >::iterator it = edges.begin(); it != edges.end(); it++) {
        addEdge(it->first.first, it->first.second, it->second);
    }
    while (!heap.empty()) {
        heap.pop();
    }
    heap.push(make_pair(-dist[s], s));
    while (!heap.empty()) {
        pair<int, int> ret = heap.top();
        heap.pop();
        int real = -ret.first - dist[ret.second];
        if (ret.second == t) {
            if (!--k) {
                return real;
            }
        }
        for (int i = firstEdge[ret.second]; i != -1; i = nextEdge[i]) {
            heap.push(make_pair(-(real + length[i] + dist[to[i]]), to[i]));
        }
    }
    return -1;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        vector<pair<pair<int, int>, int> > edges;
        edges.clear();

        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &t);
            edges.push_back(make_pair(make_pair(a, b), t));
        }
        scanf("%d%d%d", &s, &t, &k);
        if (s == t) k++;

        printf("%d\n", solve(edges, s, t, k));
    }
    return 0;
}
