#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
using namespace std;

int y, m, d;

int main() {
    while (~scanf("%d-%d-%d", &y, &m, &d)) {
        int dd = 0;

        int t = (y - 1) / 100;
        d += t - t / 4;
        if ((y % 400 != 0 && y % 100 == 0) && m > 2) {
            d++;
        }
        d--;

        int dm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        while (d > dm[m]) {
            if (m == 2 && (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))) {
                if (d == 29) {
                    break;
                } else {
                    d--;
                }
            }

            d -= dm[m];
            m++;
            if (m > 12) {
                m = 1;
                y++;
            }
        }

        printf("%.4d-%.2d-%.2d\n", y, m, d);
    }
    return 0;
}
