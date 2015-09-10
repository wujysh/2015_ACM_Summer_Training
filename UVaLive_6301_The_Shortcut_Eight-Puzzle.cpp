#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 362880;  // 9! = 362880
const int dx[5] = {-1, 1, 0, 0, 1};
const int dy[5] = {0, 0, -1, 1, -1};
const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};  // C(n, m)
const char dir[] = "udlra";

bool visited[MAXN];
int pre[MAXN], q[MAXN], head, tail, target_v, ans, nCase;
char action[MAXN];

struct Node {
    //int cnt;
    char puzzle[9];
    char xy;
} start, target;

int Kangtuo(const char *s) {  //康托展开
    int num = 0;
    for (int i = 0; i < 8; i++) {
        int temp = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i])
                temp++;
        num += fac[s[i] - 1] * temp;
    }
    return num;
}

Node ReKangtuo(int num) {  //康托逆展开
    Node tmp;
    int i, a[9];
    for (i = 2; i <= 9; i++) {
        a[i - 1] = num % i;
        num = num / i;
        tmp.puzzle[i - 1] = 0;
    }
    tmp.puzzle[0] = 0;
    for (int k = 9; k >= 2; k--) {
        int t = 0;
        for (i = 8; i >= 0; i--) {
            if (tmp.puzzle[i] != 0) continue;
            if (t == a[k - 1]) break;
            t++;
        }
        tmp.puzzle[i] = k;
    }
    for (i = 0; i < 9; i++)
        if (tmp.puzzle[i] == 0) {
            tmp.puzzle[i] = 1;
            break;
        }
    tmp.xy = 8 - a[8];
    return tmp;
}

void BFS() {
    memset(visited, false, sizeof(visited));
    int u = Kangtuo(start.puzzle);
    pre[u] = -1;
    visited[u] = 1;

    head = tail = 0;
    q[tail++] = u;

    while (head < tail) {

        u = q[head];
        head++;//cout << u << endl;

        Node cur = ReKangtuo(u);

        int xy = cur.xy;
        int x = xy / 3;
        int y = xy % 3;
        for (int i = 0; i < 5; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx <= 2 && ny >= 0 && ny <= 2) {
                Node tmp = cur;
                tmp.xy = nx * 3 + ny;

                //tmp.cnt = cur.cnt + 1;

                char t = tmp.puzzle[xy];
                tmp.puzzle[xy] = tmp.puzzle[tmp.xy];
                tmp.puzzle[tmp.xy] = t;

                int v = Kangtuo(tmp.puzzle);
                if (!visited[v]) {//cout << "!!!!" << endl;;
                    action[v] = i;
                    visited[v] = true;
                    pre[v] = u;
                    if (v == target_v) {
                        //ans = tmp.cnt;
                        return;
                    }
                    q[tail++] = v;//cout << "@@@" << endl;
                }
            }
        }
    }
}

void printPath() {
    int n = 1, u;
    char path[1000];
    path[0] = action[target_v];
    u = pre[target_v];
    while (pre[u] != -1) {
        path[n++] = action[u];
        u = pre[u];
    }
    printf("%d\n", n);
    //for (int i = n - 1; i >= 0; i--)
    //    printf("%c", dir[path[i]]);
}

void solve() {
    char str[4];
    //start.cnt = 0;
    for (int i = 0; i < 9; i++) {
        scanf("%s", str);
        if (str[0] == '0') {
            start.puzzle[i] = 9;
            start.xy = i;
        } else {
            start.puzzle[i] = str[0] - '0';
        }
    }

    for (int i = 0; i < 9; i++) {
        scanf("%s", str);
        if (str[0] == '0') {
            target.puzzle[i] = 9;
            target.xy = i;
        } else {
            target.puzzle[i] = str[0] - '0';
        }
    }
    target_v = Kangtuo(target.puzzle);
    //cout << target_v << endl;

    BFS();

    if (visited[target_v]) {
        printPath();
        //printf("%d\n", ans);
    } else {
        printf("-1\n");
    }
}

int main() {
    scanf("%d", &nCase);
    getchar();
    while (nCase--) {
        solve();
    }
    return 0;
}
