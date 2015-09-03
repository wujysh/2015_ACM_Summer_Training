#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100010;

int n, x;
long long a[MAXN];

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long Min = a[x];
    int id = x;
    for (int i = x-1; i >= 1; i--) {
        if (a[i] < Min) {
            Min = a[i];
            id = i;
        }
    }
    for (int i = n; i > x; i--) {
        if (a[i] < Min) {
            Min = a[i];
            id = i;
        }
    }

    if (Min >= 1) {
        for (int i = 1; i <= n; i++) {
            a[i] -= Min;
        }
        a[id] = Min * n;
    }

    if (x >= id) {
        for (int i = x; i > id; i--) {
            a[i]--;
        }
        a[id] += x - id;
    } else {
        for (int i = 1; i <= x; i++) {
            a[i]--;
        }
        for (int i = id + 1; i <= n; i++) {
            a[i]--;
        }
        a[id] += x + n-id;
    }

    for (int i = 1; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << a[n] << endl;

    return 0;
}
