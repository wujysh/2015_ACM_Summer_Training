#include <iostream>
#include <cstdio>
using namespace std;

long long x, y, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> x >> y >> m;

    if (x > y) swap(x, y);
    if (y >= m) {
        cout << 0 << endl;
    } else {
        if (y <= 0) {
            cout << -1 << endl;
        } else {
            long long cnt = 0;
            if (x < 0 && y > 0) {
                cnt = (-x+y-1) / y;
                x += cnt * y;
            }
            while (y < m) {
                long long t = y;
                y = x + y;
                x = t;
                cnt++;
            }
            cout << cnt << endl;
        }
    }

    return 0;
}
