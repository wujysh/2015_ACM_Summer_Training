#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 2;
const int mod = 10000;
int n, nn;

struct Mat {
    long long mat[MAXN][MAXN];
} inputMat, baseMat;

Mat operator *(Mat a, Mat b) {
    Mat c;
    memset(c.mat, 0, sizeof(c.mat));
    for (int k = 0 ; k < n ; k++) {
        for (int i = 0 ; i < n ; i++) {
            if (a.mat[i][k] == 0) continue; //优化
            for (int j = 0 ; j < n ; j++) {
                if (b.mat[k][j] == 0) continue; //优化
                c.mat[i][j] = (c.mat[i][j] + (a.mat[i][k] * b.mat[k][j]) % mod) % mod;
            }
        }
    }
    return c;
}

Mat operator ^(Mat a, int k) {
    Mat c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c.mat[i][j] = (i == j);
    for (; k ; k >>= 1) {
        if (k & 1) c = c * a;
        a = a * a;
    }
    return c;
}

void init() {
    n = 2;
    memset(baseMat.mat, 0, sizeof(baseMat.mat));
    baseMat.mat[0][0] = baseMat.mat[0][1] = baseMat.mat[1][0] = 1;
    baseMat.mat[1][1] = 0;
}

void output(Mat m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << m.mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {
    Mat ansMat = baseMat ^ nn;
    printf("%I64d\n", ansMat.mat[0][1]);
}

int main() {
    while (~scanf("%d", &nn) && nn != -1) {
        init();
        solve();
    }
    return 0;
}
